#include "Gamerun.h"



Gamerun::Gamerun()
{	

}

void Gamerun::run()
{
	//Inputs files for reading
	ifstream enemyShips("Objects/enemyship.txt");
	ifstream hsFile("Objects/highscore.txt");
	static bool played = false;
	static bool pressed = false;

	//Stores values from enemyShips into enemy_ships array
	for (int i = 0; i < 4; i++)
	{
		enemyShips >> ENEMY_SHIPS[i].name >> ENEMY_SHIPS[i].dimensionx >> ENEMY_SHIPS[i].dimensiony;
	}
	enemyShips.close();

	//Stores values from highscore txt file into highsore array
	for (int i = 0; i < 4; i++)
	{
		hsFile >> highScore[i].name >> highScore[i].score;
	}
	hsFile.close();

	//Varibles for finding highest Score
	int indexHighestScore;
	double highestScore;

	indexHighestScore = 0;
	highestScore = highScore[indexHighestScore].score;

	//Randomly picks a enemy ship from the array and loads the texture
	srand(time(0));
	string randomEnemy = ENEMY_SHIPS[rand() % 4].name;
	Texture textureRandomEnemy = textureLoad(randomEnemy);

	//Finds the image dimensions
	for (int i = 0; i < 4; i++)
	{
		if (randomEnemy == ENEMY_SHIPS[i].name)
		{
			enemyX = ENEMY_SHIPS[i].dimensionx;
			enemyY = ENEMY_SHIPS[i].dimensiony;
		}
	}

	//Creates window with default style and dimensions
	RenderWindow window(VideoMode(MAX_WIDTH, MAX_HEIGHT), "Space Shooter");
	window.setFramerateLimit(60);

	//Background
	Texture textureBG;
	textureBG = textureLoad("space-shooter/backgrounds/6.png");
	Sprite spriteBG;
	spriteBG.setTexture(textureBG);
	spriteBG.setScale(Vector2f(MAX_WIDTH / spriteBG.getLocalBounds().width, MAX_HEIGHT / spriteBG.getLocalBounds().height));

	//Menu Background
	Texture textureMenuBG;
	textureMenuBG = textureLoad("space-shooter/backgrounds/4.png");
	Sprite spriteMenuBG;
	spriteMenuBG.setTexture(textureMenuBG);
	spriteMenuBG.setScale(Vector2f(MAX_WIDTH / spriteMenuBG.getLocalBounds().width, MAX_HEIGHT / spriteMenuBG.getLocalBounds().height));

	//Set the icon
	Image icon;
	if (!icon.loadFromFile("space-shooter/backgrounds/planet-1.png"))
	{
		cout << "failure" << endl;
		return;
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	//Sets the fonts
	Font font_pixel;
	font_pixel = fontLoad("Objects/Pixel.ttf");

	Font font_space;
	font_space = fontLoad("Objects/space age.ttf");

	Font future_thin;
	future_thin = fontLoad("Objects/kenvector_future_thin.ttf");

	//Sets the music
	Music bgMusic;
	bgMusic.openFromFile("space-shooter/music/1.ogg");
	//Plays music
	bgMusic.play();
	bgMusic.setVolume(30);
	bgMusic.setLoop(true);

	//Sets base sound objects
	Sound pickupSounds;
	Sound enemySounds;
	Sound playerSounds;
	Sound bossSounds;
	Sound buttonSounds;

	//Loads a sound for the coin pickup
	SoundBuffer coinSound;
	coinSound.loadFromFile("space-shooter/sounds/gold-2.wav");

	//Loads a sound for the powerup pickup
	SoundBuffer powerupSound;
	powerupSound.loadFromFile("space-shooter/sounds/power-up-4.wav");

	//Loads a sound for the projectile
	SoundBuffer projectileSound;
	projectileSound.loadFromFile("space-shooter/sounds/laser.wav");

	//Loads a sound for a destroyed enemy
	SoundBuffer enemyDestroyedSound;
	enemyDestroyedSound.loadFromFile("space-shooter/sounds/enemyexplosion.wav");

	//Loads a sound for buttons
	SoundBuffer buttonpressSound;
	buttonpressSound.loadFromFile("space-shooter/sounds/buttonselect.wav");

	//Loads a player sprite to display
	Texture texturePlayer;
	texturePlayer = textureLoad("space-shooter/ships/2.png");

	//Loads a boss sprite to display
	Texture textureBoss;
	textureBoss = textureLoad("space-shooter/ships/8.png");

	//Loads a coin sprite to display
	Texture textureCoin;
	textureCoin = textureLoad("space-shooter/items/gem-3.png");

	//Loads powerup sprite to display
	Texture texturePowerUp;
	texturePowerUp = textureLoad("space-shooter/items/power-up-1.png");

	Texture texturePowerUp1;
	texturePowerUp1 = textureLoad("space-shooter/items/power-up-2.png");

	//Loads a projectile sprite to display
	Texture textureProjectile;
	textureProjectile = textureLoad("space-shooter/shots/spritesheet.png");

	//Loads hud:health sprite to display
	Texture textureHealthBar;
	textureHealthBar = textureLoad("space-shooter/hud/health-bar.png");
	Texture textureHealth;
	textureHealth = textureLoad("space-shooter/hud/health-bar-fill.png");

	//Loads particle texture to display
	Texture textureParticle;
	textureParticle = textureLoad("space-shooter/backgrounds/star-4.png");

	//Health bar Object
	class hud healthBar;
	healthBar.sprite.setTexture(textureHealthBar);
	healthBar.rect.setPosition(Vector2f(0, 0));

	//Health Object
	class hud health;
	health.sprite.setTexture(textureHealth);
	health.rect.setPosition(healthBar.rect.getPosition().x + 8.8f, healthBar.rect.getPosition().y + 7);
	health.sprite.setTextureRect(IntRect(0, 0, 80, 18));
	health.picWidth = 80;
	health.math = health.picWidth / health.health;

	//Player Object
	class player Player1;
	Player1.sprite.setTexture(texturePlayer);

	//Projectile Vector Array
	vector<projectile>::const_iterator projectileIter;
	vector<projectile> projectileArray;

	//Projectile Object
	class projectile projectile1;
	projectile1.sprite.setTexture(textureProjectile);
	projectile1.sprite.setTextureRect(IntRect(0, 0, 14, 22));

	//Enemy Vector Array
	vector<enemy>::const_iterator enemyIter;
	vector<enemy> enemyArray;

	//enemy Object
	class enemy enemy1;
	enemy1.sprite.setTexture(textureRandomEnemy);
	enemy1.rect.setSize(Vector2f(enemyX, enemyY));
	enemy1.rect.setOrigin(Vector2f(enemy1.sprite.getLocalBounds().width, enemy1.sprite.getLocalBounds().height));
	//enemy1.rect.setPosition(MAX_WIDTH / 2, -2);
	//enemyArray.push_back(enemy1);

	//Boss Objects
	class enemy boss1;
	boss1.sprite.setTexture(textureBoss);
	boss1.rect.setSize(Vector2f(boss1.sprite.getLocalBounds().width, boss1.sprite.getLocalBounds().height));
	boss1.hp = 50;
	boss1.movementSpeed = 1;
	boss1.isBoss = true;

	//Text Vector Array
	vector<textDisplay>::const_iterator textIter;
	vector<textDisplay> textDisplayArray;

	//Text Object
	class textDisplay textDisplay1;
	textDisplay1.text.setFont(font_pixel);

	//Score Text Object
	class textDisplay scoreDisplay;
	scoreDisplay.text.setFont(font_pixel);
	scoreDisplay.text.setColor(sf::Color::White);
	scoreDisplay.text.setCharacterSize(15);
	scoreDisplay.text.setPosition(0, 35);

	//Title Text Object
	class textDisplay titleText;
	titleText.text.setFont(font_space);
	titleText.text.setColor(Color::White);

	//Play Game Object
	class textDisplay playText;
	playText.text.setFont(font_pixel);

	//Exit Text Object
	class textDisplay exitText;
	exitText.text.setFont(font_pixel);

	//Highscore text Object
	class textDisplay highscoresText;
	highscoresText.text.setFont(font_pixel);

	//Score text object
	class textDisplay playerScore;
	playerScore.text.setFont(font_pixel);

	//Player name text object
	pName.setFont(font_pixel);

	//Score 3 text object
	score3.setFont(font_pixel);

	//Score 4 text object
	score4.setFont(font_pixel);

	//Pickupitem Vector Array
	vector<pickup>::const_iterator pickupIter;
	vector<pickup> pickupArray;

	//Pickupitem Object
	class pickup pickupItem;
	pickupItem.sprite.setTexture(textureCoin);

	//particle Object
	class Particles particleSystem;
	particleSystem.system.setTexture(textureParticle);
	thor::PolarVector2f velocity(30.f, 90.f);

	//Initialize window
	while (window.isOpen())
	{
		//Checks all window's events
		Event event;
		while (window.pollEvent(event))
		{
			//Closes the window: exit or escape
			if ((event.type == Event::Closed) || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			{
				window.close();
			}

			//Texts in keyboard input 
			if (gameState == "HighScore")
			{
				if (event.type == sf::Event::TextEntered)
				{
					if ((event.KeyPressed == sf::Keyboard::BackSpace) && (pString.size() != 0))
					{
						pString.pop_back();
						
					}
					else if (event.text.unicode < 128)
					{
						if (pString.size() <= 2)
						{
							pString += (char)event.text.unicode;
							pName.setString(pString);
						}
					}
				}
			}
		}

		window.clear();

		//Get the mouse's position relative to the window
		Vector2i mousePos = Mouse::getPosition(window);
		entity mouseRect;
		mouseRect.rect.setFillColor(Color::Blue);
		mouseRect.rect.setSize(Vector2f(8, 8));

		//Links mouse rectangle to the pos of the mouse
		mouseRect.rect.setPosition(Vector2f(mousePos.x, mousePos.y));

		//Show Menu Screen
		if (gameState == "Menu")
		{
			buttonSounds.setBuffer(buttonpressSound);
			
			
			//Set 'Title' text settings
			titleText.text.setCharacterSize(40);
			titleText.text.setString("  Welcome to\nSpace Shooter");
			titleText.text.setColor(Color(148, 88, 201));
			titleText.text.setPosition(Vector2f(MAX_WIDTH / 2 - titleText.text.getGlobalBounds().width / 2, 20));

			//Set 'Play' text settings
			playText.text.setString("PLAY!");
			playText.text.setColor(Color(148, 88, 201));
			playText.text.setPosition(Vector2f(MAX_WIDTH/2-playText.text.getGlobalBounds().width/2, 200));

			//Set 'Highscores' text settings
			highscoresText.text.setString("HIGHSCORES");
			highscoresText.text.setColor(Color(148, 88, 201));
			highscoresText.text.setPosition(Vector2f(MAX_WIDTH / 2 - highscoresText.text.getGlobalBounds().width / 2, 380));

			//Set 'Exit' text settings
			exitText.text.setString("EXIT");
			exitText.text.setColor(Color(148, 88, 201));
			exitText.text.setPosition(Vector2f(MAX_WIDTH / 2 - exitText.text.getGlobalBounds().width / 2, 560));

			//Mouse collision with text
			if (playText.rect.getGlobalBounds().intersects(mouseRect.rect.getGlobalBounds()))
			{
				
				if (!played)
				{
					buttonSounds.play();
					played = true;
				}

				//Starts Game
				playText.text.setColor(Color(148, 88, 201,200));
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					gameState = "Game";
				}
			}

			else if (highscoresText.rect.getGlobalBounds().intersects(mouseRect.rect.getGlobalBounds()))
			{
				highscoresText.text.setColor(Color(148, 88, 201, 200));
				if (!played)
				{
					buttonSounds.play();
					played = true;
				}

				//Open highscores screen
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					gameState = "HighScore";
				}
			}

			else if (exitText.rect.getGlobalBounds().intersects(mouseRect.rect.getGlobalBounds()))
			{
				exitText.text.setColor(Color(148, 88, 201, 200));
				if (!played)
				{
					buttonSounds.play();
					played = true;
				}

				//Exits Game
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					window.close();
				}

			}

			else
			{
				played = false;
			}

			//Update text rectangle pos
			playText.rectUpdate();
			titleText.rectUpdate();
			exitText.rectUpdate();
			highscoresText.rectUpdate();

			//Draw Text objects
			window.draw(titleText.text);
			window.draw(playText.text);
			window.draw(highscoresText.text);
			window.draw(exitText.text);
	
		}

		//Show highscores Screen
		if (gameState == "HighScore")
		{
			if (Player1.hp <= 0)
			{

				//Set 'Title' text settings
				titleText.text.setCharacterSize(40);
				titleText.text.setColor(Color(148, 88, 201));
				titleText.text.setPosition(Vector2f(MAX_WIDTH / 2 - titleText.text.getGlobalBounds().width / 2, 20));
				titleText.text.setString("You Lose");

				//Set 'PlayerScore' text settings
				playerScore.text.setCharacterSize(20);
				playerScore.text.setColor(Color(148, 88, 201));
				playerScore.text.setPosition(Vector2f(MAX_WIDTH / 2 - playerScore.text.getGlobalBounds().width / 2, 150));
				playerScore.text.setString("Your score was:");

				//Set 'Highscores' text settings
				highscoresText.text.setCharacterSize(20);
				highscoresText.text.setColor(Color(148, 88, 201));
				highscoresText.text.setPosition(Vector2f(MAX_WIDTH / 2 - highscoresText.text.getGlobalBounds().width / 2, 180));
				highscoresText.text.setString(to_string(Player1.score));

				//Set 'Name' text settings
				playText.text.setCharacterSize(20);
				playText.text.setString("Enter your initials");
				playText.text.setColor(Color(148, 88, 201));
				playText.text.setPosition(Vector2f(MAX_WIDTH / 2 - playText.text.getGlobalBounds().width / 2, 250));

				//Set 'Name' text settings
				pName.setCharacterSize(25);
				pName.setColor(Color(148, 88, 201));
				pName.setPosition(Vector2f(MAX_WIDTH / 2 - pName.getGlobalBounds().width / 2, 280));

				//Updates highscores system

				if (Keyboard::isKeyPressed(Keyboard::Return))
				{
					if (Player1.score > highScore[3].score)
					{
						highScore[3].score = Player1.score;
						highScore[3].name = pString;
					}
					window.close();
				}
				window.draw(titleText.text);
				window.draw(playerScore.text);
				window.draw(highscoresText.text);
				window.draw(playText.text);
				window.draw(pName);
			}
			else
			{
				//Set Score1 text settings
				titleText.text.setFont(font_pixel);
				titleText.text.setCharacterSize(40);
				titleText.text.setColor(Color(148, 88, 201));
				titleText.text.setPosition(Vector2f(MAX_WIDTH / 4 - titleText.text.getGlobalBounds().width / 2, 100));
				titleText.text.setString(highScore[0].name);

				pName.setCharacterSize(40);
				pName.setColor(Color(148, 88, 201));
				pName.setPosition(Vector2f(MAX_WIDTH / 4 + pName.getGlobalBounds().width + 50, 100));
				pName.setString(to_string(highScore[0].score));

				//Set Score2 text settings
				playerScore.text.setCharacterSize(40);
				playerScore.text.setColor(Color(148, 88, 201));
				playerScore.text.setPosition(Vector2f(MAX_WIDTH / 4 - playerScore.text.getGlobalBounds().width / 2, 180));
				playerScore.text.setString(highScore[1].name);

				exitText.text.setCharacterSize(40);
				exitText.text.setColor(Color(148, 88, 201));
				exitText.text.setPosition(Vector2f(MAX_WIDTH / 4 + exitText.text.getGlobalBounds().width + 50, 180));
				exitText.text.setString(to_string(highScore[1].score));

				//Set Score 3 text settings
				highscoresText.text.setCharacterSize(40);
				highscoresText.text.setColor(Color(148, 88, 201));
				highscoresText.text.setPosition(Vector2f(MAX_WIDTH / 4 - highscoresText.text.getGlobalBounds().width / 2, 260));
				highscoresText.text.setString(highScore[2].name);

				score3.setCharacterSize(40);
				score3.setColor(Color(148, 88, 201));
				score3.setPosition(Vector2f(MAX_WIDTH / 4 + score3.getGlobalBounds().width + 50, 260));
				score3.setString(to_string(highScore[2].score));

				//Set Score 4 text settings
				playText.text.setCharacterSize(40);
				playText.text.setColor(Color(148, 88, 201));
				playText.text.setPosition(Vector2f(MAX_WIDTH / 4 - playText.text.getGlobalBounds().width / 2, 340));
				playText.text.setString(highScore[3].name);

				score4.setCharacterSize(40);
				score4.setColor(Color(148, 88, 201));
				score4.setPosition(Vector2f(MAX_WIDTH / 4 + pName.getGlobalBounds().width + 50, 340));
				score4.setString(to_string(highScore[3].score));

				if (Keyboard::isKeyPressed(Keyboard::BackSpace))
				{
					gameState = "Menu";
				}

				window.draw(titleText.text);
				window.draw(playerScore.text);
				window.draw(highscoresText.text);
				window.draw(playText.text);
				window.draw(pName);
				window.draw(exitText.text);
				window.draw(score3);
				window.draw(score4);
			}
		}

		//Run Game
		if (gameState == "Game")
		{
			//Update particle system
			particleSystem.system.update(particleClock.restart());

			//Set particle position to the player
			particleSystem.emitter.setParticlePosition(Vector2f(Player1.sprite.getPosition().x, Player1.sprite.getPosition().y + 15));
			particleSystem.emitter.setParticleVelocity(thor::Distributions::deflect(velocity, 90.f));

			//Elapsed Timers
			Time projectileElapsed = projectileClock.getElapsedTime();
			Time collisionElapsed = collisionClock.getElapsedTime();
			Time pickupElapsed = PickupClock.getElapsedTime();
			Time projectileElapsed1 = projectileClock1.getElapsedTime();
			Time spawnElapsed = enemy1.enemySpawnClock.getElapsedTime();
			Time spawnBossElapsed = boss1.enemySpawnClock.getElapsedTime();
			Time powerUpElapsed = Player1.powerUpClock.getElapsedTime();

			//Player collides with boundaries
			Player1.wallCollision(MAX_WIDTH, 20);

			//Shows gameover screen if player dies
			if (Player1.hp <= 0)
			{
				gameState = "HighScore";
			}

			//Player collides with pickup
			universalCounter = 0;
			for (pickupIter = pickupArray.begin(); pickupIter != pickupArray.end(); pickupIter++)
			{
				if (Player1.rect.getGlobalBounds().intersects(pickupArray[universalCounter].rect.getGlobalBounds()))
				{
					if (pickupArray[universalCounter].isCoin == true)
					{
						Player1.score += pickupArray[universalCounter].coinValue;
						pickupSounds.setBuffer(coinSound);
						pickupSounds.play();
					}
					else if (pickupArray[universalCounter].isPowerup_Fast == true)
					{
						Player1.powerUp_FireRate = true;
						Player1.powerUp_Triple = false;
						pickupSounds.setBuffer(powerupSound);
						pickupSounds.play();
					}
					else if (pickupArray[universalCounter].isPowerup_Triple == true)
					{
						Player1.powerUp_Triple = true;
						Player1.powerUp_FireRate = false;
						pickupSounds.setBuffer(powerupSound);
						pickupSounds.play();
					}
					pickupArray[universalCounter].destroy = true;
				}

				universalCounter++;
			}

			//Sets a timer for how longer player can have a powerup
			if (Player1.powerUp_FireRate == true || Player1.powerUp_Triple == true)
			{
				if (powerUpElapsed.asSeconds() >= Player1.powerUpTime)
				{
					Player1.powerUpClock.restart();
					Player1.powerUp_FireRate = false;
					Player1.powerUp_Triple = false;
				}
			}

			//Enemy collides with player
			if (collisionElapsed.asSeconds() >= 0.5)
			{
				collisionClock.restart();

				universalCounter = 0;
				for (enemyIter = enemyArray.begin(); enemyIter != enemyArray.end(); enemyIter++)
				{
					if (Player1.rect.getGlobalBounds().intersects(enemyArray[universalCounter].rect.getGlobalBounds()))
					{
						//Text Display
						textDisplay1.text.setString(to_string(enemyArray[universalCounter].attackDamage));
						textDisplay1.text.setPosition(Player1.rect.getPosition().x - Player1.rect.getSize().x / 2,
							Player1.rect.getPosition().y - Player1.rect.getSize().y / 2);
						textDisplayArray.push_back(textDisplay1);

						//Removes hp & update healthbar
						Player1.hp -= enemyArray[universalCounter].attackDamage;
						health.updateHealth();
						health.picWidth -= health.math*health.damage;
						//cout << health.picWidth << endl;	//Debug Healthbar With

						Player1.powerUp_FireRate = false;
						Player1.powerUp_Triple = false;
					}
					universalCounter++;
				}
			}

			//cout << Player1.hp << endl; //Debug Health HP

			// Projectile collides with enemy
			universalCounter = 0;
			for (projectileIter = projectileArray.begin(); projectileIter != projectileArray.end(); projectileIter++)
			{
				collisionCounter = 0;
				for (enemyIter = enemyArray.begin(); enemyIter != enemyArray.end(); enemyIter++)
				{
					if (projectileArray[universalCounter].rect.getGlobalBounds().intersects(enemyArray[collisionCounter].rect.getGlobalBounds()))
					{
						projectileArray[universalCounter].destroy = true;

						//Damage Text Display
						textDisplay1.text.setString(to_string(projectileArray[universalCounter].attackDamage));
						textDisplay1.text.setPosition(enemyArray[collisionCounter].rect.getPosition().x - enemyArray[collisionCounter].rect.getSize().x / 2,
							enemyArray[collisionCounter].rect.getPosition().y - enemyArray[collisionCounter].rect.getSize().y / 2);
						textDisplayArray.push_back(textDisplay1);

						enemyArray[collisionCounter].hp -= projectileArray[universalCounter].attackDamage;
						//Debug Enemy HP & Attack damage
						//cout << "HP left " << enemyArray[collisionCounter].hp << " attack damage " << projectileArray[universalCounter].attackDamage << endl;

						if (enemyArray[collisionCounter].hp <= 0)
						{
							enemyArray[collisionCounter].alive = false;
							enemySounds.setBuffer(enemyDestroyedSound);
							enemySounds.play();
							Player1.score += enemyArray[collisionCounter].deathValue;
						}

						if ((enemyArray[collisionCounter].isBoss == true) && (enemyArray[collisionCounter].hp <= 0))
						{
							boss1.spawned = false;
							enemy1.enemySpawnRate = 0.5;
						}
					}
					collisionCounter++;
				}
				universalCounter++;
			}

			//Delete Dead Enemy
			universalCounter = 0;
			for (enemyIter = enemyArray.begin(); enemyIter != enemyArray.end(); enemyIter++)
			{
				if (enemyArray[universalCounter].alive == false)
				{
					//cout << "Enemy destroyed" << endl; //Debug for Enemy Destroyed

					//Place coin at enemy position
					if (generateRandom(pickupItem.coinChance) == 1)
					{
						pickupItem.isCoin = true;
						pickupItem.isPowerup_Fast = false;
						pickupItem.isPowerup_Triple = false;
						pickupItem.sprite.setTexture(textureCoin);
						pickupItem.rect.setPosition(enemyArray[universalCounter].rect.getPosition().x - enemyArray[universalCounter].rect.getSize().x,
							enemyArray[universalCounter].rect.getPosition().y - enemyArray[universalCounter].rect.getSize().y);
						pickupArray.push_back(pickupItem);
					}

					//place powerup: fast shot at enemy position
					if (generateRandom(pickupItem.powerUpChance) == 1) //20% chance
					{
						pickupItem.isCoin = false;
						pickupItem.isPowerup_Triple = false;
						pickupItem.isPowerup_Fast = true;
						pickupItem.sprite.setTexture(texturePowerUp);
						pickupItem.rect.setSize(Vector2f(24, 19));
						pickupItem.sprite.setTextureRect(IntRect(0, 0, 24, 19));
						pickupItem.rect.setPosition(enemyArray[universalCounter].rect.getPosition().x - enemyArray[universalCounter].rect.getSize().x,
							enemyArray[universalCounter].rect.getPosition().y - enemyArray[universalCounter].rect.getSize().y);
						pickupArray.push_back(pickupItem);
					}

					//Place powerup: triple shot at enemy position
					if (generateRandom(pickupItem.powerUpChance) == 1) //20% chance
					{
						pickupItem.isCoin = false;
						pickupItem.isPowerup_Triple = true;
						pickupItem.isPowerup_Fast = false;
						pickupItem.sprite.setTexture(texturePowerUp1);
						pickupItem.rect.setSize(Vector2f(24, 19));
						pickupItem.sprite.setTextureRect(IntRect(0, 0, 24, 19));
						pickupItem.rect.setPosition(enemyArray[universalCounter].rect.getPosition().x - enemyArray[universalCounter].rect.getSize().x,
							enemyArray[universalCounter].rect.getPosition().y - enemyArray[universalCounter].rect.getSize().y);
						pickupArray.push_back(pickupItem);
					}

					enemyArray.erase(enemyIter);
					break;
				}
				universalCounter++;
			}

			//Delete projectile
			universalCounter = 0;
			for (projectileIter = projectileArray.begin(); projectileIter != projectileArray.end(); projectileIter++)
			{
				if (projectileArray[universalCounter].destroy == true)
				{
					//cout << "projectile destroyed" << endl; //Debug for projectile destroyed
					projectileArray.erase(projectileIter);
					break;
				}

				universalCounter++;
			}

			//Delete text
			universalCounter = 0;
			for (textIter = textDisplayArray.begin(); textIter != textDisplayArray.end(); textIter++)
			{
				if (textDisplayArray[universalCounter].destroy == true)
				{
					textDisplayArray.erase(textIter);
					break;
				}
				universalCounter++;
			}

			//Delete Pickup
			universalCounter = 0;
			for (pickupIter = pickupArray.begin(); pickupIter != pickupArray.end(); pickupIter++)
			{
				if (pickupArray[universalCounter].destroy == true)
				{
					pickupArray.erase(pickupIter);
					break;
				}
				universalCounter++;
			}

			//Draw background
			window.draw(spriteBG);

			//Enables particle system
			window.draw(particleSystem.system);

			//Spawn Enemies
			if (spawnElapsed.asSeconds() >= enemy1.enemySpawnRate)
			{
				enemy1.enemySpawnClock.restart();
				enemy1.rect.setPosition(generateRandom(window.getSize().x), -100);
				enemyArray.push_back(enemy1);
			}

			//Spawn Boss
			if (boss1.spawned == false)
			{
				if (Player1.score / 1000 > boss_apperance)
				{
					boss_apperance++;
					//spawn boss
					boss1.rect.setPosition(generateRandom(window.getSize().x), 100);
					enemyArray.push_back(boss1);
					boss1.spawned = true;

					//Reduces enemy spawn rate
					enemy1.enemySpawnRate = 5;
				}
			}

			//Fire projectile (Space Bar)
			if (projectileElapsed.asSeconds() >= fireRate)
			{
				projectileClock.restart();

				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					//Plays projectile sound
					playerSounds.setBuffer(projectileSound);
					playerSounds.play();

					if (Player1.powerUp_Triple == true) //Powerup attack: triple shot
					{
						projectile1.rect.setPosition(Player1.rect.getPosition().x, Player1.rect.getPosition().y);
						projectileArray.push_back(projectile1);

						projectile1.rect.setPosition(Player1.rect.getPosition().x - 12, Player1.rect.getPosition().y);
						projectileArray.push_back(projectile1);

						projectile1.rect.setPosition(Player1.rect.getPosition().x + 12, Player1.rect.getPosition().y);
						projectileArray.push_back(projectile1);
					}

					if (Player1.powerUp_FireRate == true) //Powerup attack: fast shot
					{
						fireRate = 0.05;
						projectile1.rect.setPosition(Player1.rect.getPosition().x - 5, Player1.rect.getPosition().y);
						projectileArray.push_back(projectile1);
					}

					else //Normal attack
					{
						fireRate = 0.4;
						projectile1.rect.setPosition(Player1.rect.getPosition().x - 5, Player1.rect.getPosition().y);
						projectileArray.push_back(projectile1);
					}
				}
			}

			//Draw Pickup
			universalCounter = 0;
			for (pickupIter = pickupArray.begin(); pickupIter != pickupArray.end(); pickupIter++)
			{
				pickupArray[universalCounter].update();
				if (pickupElapsed.asSeconds() >= 0.1)
				{
					PickupClock.restart();
					if (pickupArray[universalCounter].isCoin == true)
					{
						pickupArray[universalCounter].animate();
					}

				}
				//cout << pickupArray[universalCounter].universalCounter << endl; //Debug Pickup array counter
				//window.draw(pickupArray[universalCounter].rect); //Debug Rectangle of projectile
				window.draw(pickupArray[universalCounter].sprite);
				universalCounter++;
			}



			//Draw Projectile
			universalCounter = 0;
			for (projectileIter = projectileArray.begin(); projectileIter != projectileArray.end(); projectileIter++)
			{
				projectileArray[universalCounter].update(); // Update projectile
				if (projectileElapsed1.asSeconds() >= 0.2)
				{
					projectileClock1.restart();
					projectileArray[universalCounter].updateAnimation();
				}
				//window.draw(projectileArray[universalCounter].rect);
				window.draw(projectileArray[universalCounter].sprite);
				universalCounter++;
			}

			//Draw Enemy
			universalCounter = 0;
			for (enemyIter = enemyArray.begin(); enemyIter != enemyArray.end(); enemyIter++)
			{
				enemyArray[universalCounter].wallCollision(MAX_WIDTH, enemyX, MAX_HEIGHT - 400, 87);
				enemyArray[universalCounter].update();
				enemyArray[universalCounter].updateMovement();
				//window.draw(enemyArray[universalCounter].rect); //Debug Draw Enemy's rectangle
				window.draw(enemyArray[universalCounter].sprite);
				//cout << enemyArray[universalCounter].rect.getPosition().y << endl; //Debug Enemy X position
				universalCounter++;
			}

			//Update player
			Player1.update();
			Player1.updateMovement();

			//Draw Player
			//window.draw(Player1.rect); //Debug Draw Enemy's rectangle
			window.draw(Player1.sprite);

			//Draw Text
			universalCounter = 0;
			for (textIter = textDisplayArray.begin(); textIter != textDisplayArray.end(); textIter++)
			{
				textDisplayArray[universalCounter].update();
				window.draw(textDisplayArray[universalCounter].text);

				universalCounter++;
			}

			//Draw Score
			scoreDisplay.text.setString("Score: " + to_string(Player1.score));
			window.draw(scoreDisplay.text);

			//Update health
			healthBar.update();
			health.update();

			//Draw health
			window.draw(healthBar.sprite);
			window.draw(health.sprite);
		}

		//Show 'GameOver' Screen
		if (gameState == "GameOver")
		{
			//display 'Gameover' Text
			titleText.text.setString("score: "+ to_string(Player1.score));
			titleText.text.setCharacterSize(50);
			titleText.text.setPosition(Vector2f(MAX_WIDTH/2-180, 50));

			//Display backround
			window.draw(spriteMenuBG);
			
			//Display player's score
			window.draw(titleText.text);
		}

		window.display();//End current frame

		}

		//Output file for highscores
		ofstream hsFileOut("Objects/highscore.txt");

		//Sorts Highscores
		int temp;
		string tempName;
		for (int i = 0; i <= 3; i++)
		{
			for (int j = i + 1; j <= 3; j++)
			{
				if (highScore[i].score<highScore[j].score)
				{
					temp = highScore[j].score;
					tempName = highScore[j].name;
					highScore[j].score = highScore[i].score;
					highScore[j].name = highScore[i].name;
					highScore[i].name = tempName;
					highScore[i].score = temp;
				}
			}
		}

		//Outputs scores to txt file
		for (int i = 0; i < 4; i++)
		{
			hsFileOut << highScore[i].name << " " << highScore[i].score << endl;
		}
		hsFileOut.close();

		return;
	}
Texture Gamerun::textureLoad(string filename)
{
	Texture texture;
	if (!texture.loadFromFile(filename))
	{
		sf::err;
	}
	return texture;
}

Font Gamerun::fontLoad(string filename)
{
	Font font;
	if (!font.loadFromFile(filename))
	{
		sf::err;
	}
	return font;
}





