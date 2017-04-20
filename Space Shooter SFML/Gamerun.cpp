#include "Gamerun.h"



Gamerun::Gamerun()
{	

}

void Gamerun::run()
{
	ifstream enemyShips("Objects/enemyship.txt");
	static bool played;

	//Stores values from enemyShips into enemy_ships array
	for (int i = 0; i < 4; i++)
	{
		enemyShips >> ENEMY_SHIPS[i].name >> ENEMY_SHIPS[i].dimensionx >> ENEMY_SHIPS[i].dimensiony;
	}
	enemyShips.close();

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
	//bgMusic.play();
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
	vector<projectile>::const_iterator iter;
	vector<projectile> projectileArray;

	//Projectile Object
	class projectile projectile1;
	projectile1.sprite.setTexture(textureProjectile);
	projectile1.sprite.setTextureRect(IntRect(0, 0, 14, 22));

	//Enemy Vector Array
	vector<enemy>::const_iterator iter4;
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
	vector<textDisplay>::const_iterator iter8;
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

	//Pickupitem Vector Array
	vector<pickup>::const_iterator iter11;
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

			
		}

		window.clear(/*sf::Color::Black*/);

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

			highscoresText.text.setString("HIGHSCORES");
			highscoresText.text.setColor(Color(148, 88, 201));
			highscoresText.text.setPosition(Vector2f(MAX_WIDTH / 2 - highscoresText.text.getGlobalBounds().width / 2, 380));

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

			if (highscoresText.rect.getGlobalBounds().intersects(mouseRect.rect.getGlobalBounds()))
			{
				highscoresText.text.setColor(Color(148, 88, 201, 200));
				buttonSounds.play();

				//Open highscores screen
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					gameState = "HighScore";
				}
			}

			if (exitText.rect.getGlobalBounds().intersects(mouseRect.rect.getGlobalBounds()))
			{
				exitText.text.setColor(Color(148, 88, 201, 200));
				buttonSounds.play();
				
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					window.close();
				}
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

			//played = false;
			
			
		}

		//Show highscores Screen
		if (gameState == "HighScore")
		{
			break;
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
				gameState = "GameOver";
			}

			//Player collides with pickup
			universalCounter = 0;
			for (iter11 = pickupArray.begin(); iter11 != pickupArray.end(); iter11++)
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
				for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
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
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				counter2 = 0;
				for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
				{
					if (projectileArray[universalCounter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds()))
					{
						projectileArray[universalCounter].destroy = true;

						//Damage Text Display
						textDisplay1.text.setString(to_string(projectileArray[universalCounter].attackDamage));
						textDisplay1.text.setPosition(enemyArray[counter2].rect.getPosition().x - enemyArray[counter2].rect.getSize().x / 2,
							enemyArray[counter2].rect.getPosition().y - enemyArray[counter2].rect.getSize().y / 2);
						textDisplayArray.push_back(textDisplay1);

						enemyArray[counter2].hp -= projectileArray[universalCounter].attackDamage;
						//Debug Enemy HP & Attack damage
						//cout << "HP left " << enemyArray[counter2].hp << " attack damage " << projectileArray[universalCounter].attackDamage << endl;

						if (enemyArray[counter2].hp <= 0)
						{
							enemyArray[counter2].alive = false;
							enemySounds.setBuffer(enemyDestroyedSound);
							enemySounds.play();
							Player1.score += enemyArray[counter2].deathValue;
						}

						if ((enemyArray[counter2].isBoss == true) && (enemyArray[counter2].hp <= 0))
						{
							cout << "Enemy spawn rate returned to normal" << endl;
							boss1.spawned = false;
							enemy1.enemySpawnRate = 0.5;
						}
					}
					counter2++;
				}
				universalCounter++;
			}

			//Delete Dead Enemy
			universalCounter = 0;
			for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
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

					enemyArray.erase(iter4);
					break;
				}
				universalCounter++;
			}

			//Delete projectile
			universalCounter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				if (projectileArray[universalCounter].destroy == true)
				{
					//cout << "projectile destroyed" << endl; //Debug for projectile destroyed
					projectileArray.erase(iter);
					break;
				}

				universalCounter++;
			}

			//Delete text
			universalCounter = 0;
			for (iter8 = textDisplayArray.begin(); iter8 != textDisplayArray.end(); iter8++)
			{
				if (textDisplayArray[universalCounter].destroy == true)
				{
					textDisplayArray.erase(iter8);
					break;
				}
				universalCounter++;
			}

			//Delete Pickup
			universalCounter = 0;
			for (iter11 = pickupArray.begin(); iter11 != pickupArray.end(); iter11++)
			{
				if (pickupArray[universalCounter].destroy == true)
				{
					pickupArray.erase(iter11);
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
				cout << "true " << endl;
				if (Player1.score / 1000 > boss_apperance)
				{
					cout << "boss spawn" << endl;
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
			for (iter11 = pickupArray.begin(); iter11 != pickupArray.end(); iter11++)
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
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
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
			for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
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
			for (iter8 = textDisplayArray.begin(); iter8 != textDisplayArray.end(); iter8++)
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





