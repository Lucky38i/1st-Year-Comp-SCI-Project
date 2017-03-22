#include "Gamerun.h"



Gamerun::Gamerun()
{	

}

void Gamerun::run()
{

	ifstream enemyShips("Objects/enemyship.txt");

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

	//Set the icon
	Image icon;
	if (!icon.loadFromFile("space-shooter/backgrounds/planet-1.png"))
	{
		//cout << "failure" << endl;
		return;
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//Sets the font
	Font font;
	font = fontLoad("Objects/Pixel.ttf");

	//Loads a player sprite to display
	Texture texturePlayer;
	texturePlayer = textureLoad("space-shooter/ships/2.png");

	//Loads a enemy sprite to display
	Texture textureEnemy;
	textureEnemy = textureLoad("space-shooter/ships/4.png");

	//Loads a coin sprite to display
	Texture textureCoin;
	textureCoin = textureLoad("space-shooter/items/gem-3.png");

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
	enemy1.rect.setPosition(MAX_WIDTH / 2, -2);
	enemyArray.push_back(enemy1);

	//Text Vector Array
	vector<textDisplay>::const_iterator iter8;
	vector<textDisplay> textDisplayArray;

	//Text Object
	class textDisplay textDisplay1;
	textDisplay1.text.setFont(font);

	//Score Text Object
	class textDisplay scoreDisplay;
	scoreDisplay.text.setFont(font);
	scoreDisplay.text.setColor(sf::Color::White);
	scoreDisplay.text.setCharacterSize(15);
	scoreDisplay.text.setPosition(0, 35);

	//coin Vector Array
	vector<pickup>::const_iterator iter11;
	vector<pickup> pickupArray;

	//coin Object
	class pickup coinPickup;
	coinPickup.sprite.setTexture(textureCoin);

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

		//Clear Screen
		window.clear(/*sf::Color::Black*/);

		//Update particle system
		particleSystem.system.update(particleClock.restart());

		//Set particle position to the player
		particleSystem.emitter.setParticlePosition(Vector2f(Player1.sprite.getPosition().x, Player1.sprite.getPosition().y + 15));
		particleSystem.emitter.setParticleVelocity(thor::Distributions::deflect(velocity, 90.f));

		//Elapsed Time

		sf::Time elapsed1 = projectileClock.getElapsedTime();
		sf::Time elapsed2 = collisionClock.getElapsedTime();
		sf::Time elapsed3 = PickupClock.getElapsedTime();
		sf::Time elapsed4 = projectileClock1.getElapsedTime();
		sf::Time elapsed5 = enemySpawnClock.getElapsedTime();


		//Player collides with boundaries
		if (Player1.rect.getPosition().x <= 20)
		{
			Player1.canMoveLeft = false;
		}
		else if (Player1.rect.getPosition().x >= MAX_WIDTH - 20)
		{
			Player1.canMoveRight = false;
		}
		else
		{
			Player1.canMoveLeft = true;
			Player1.canMoveRight = true;
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
				}
				pickupArray[universalCounter].destroy = true;
			}

			universalCounter++;
		}

		//Enemy collides with player
		if (elapsed2.asSeconds() >= 0.5)
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

					Player1.hp -= enemyArray[universalCounter].attackDamage;
					health.updateHealth();
					health.picWidth -= health.math*health.damage;
					cout << health.picWidth << endl;
				}
				universalCounter++;
			}
		}

		//cout << Player1.hp << endl;


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
					cout << "HP left " << enemyArray[counter2].hp << " attack damage " << projectileArray[universalCounter].attackDamage << endl;


					if (enemyArray[counter2].hp <= 0)
					{
						enemyArray[counter2].alive = false;
						Player1.score += enemyArray[counter2].deathValue;
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
				cout << "Enemy destroyed" << endl;

				//Place coin at enemy position
				if (generateRandom(dropChance) == 1)
				{
					coinPickup.rect.setPosition(enemyArray[universalCounter].rect.getPosition().x - enemyArray[universalCounter].rect.getSize().x,
						enemyArray[universalCounter].rect.getPosition().y - enemyArray[universalCounter].rect.getSize().y);
					pickupArray.push_back(coinPickup);
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
				//cout << "projectile destroyed" << endl;
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

		//Spawn Enemies (y Key)
		if (Keyboard::isKeyPressed(Keyboard::Y))
		{
			enemy1.rect.setPosition(generateRandom(window.getSize().x), generateRandom(window.getSize().y));
			enemyArray.push_back(enemy1);
		}

		//Spawn Enemies
		if (elapsed2.asSeconds() >= 0.5)
		{
			collisionClock.restart();




			//Fire projectile (Space Bar)
			if (elapsed1.asSeconds() >= 0.2)
			{
				projectileClock.restart();

				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					projectile1.rect.setPosition(Player1.rect.getPosition().x - 5, Player1.rect.getPosition().y);
					projectileArray.push_back(projectile1);

				}
			}

			//Draw Pickup
			universalCounter = 0;
			for (iter11 = pickupArray.begin(); iter11 != pickupArray.end(); iter11++)
			{
				pickupArray[universalCounter].update();
				if (elapsed3.asSeconds() >= 0.1)
				{
					PickupClock.restart();
					pickupArray[universalCounter].animate();
				}
				//cout << pickupArray[universalCounter].universalCounter << endl;
				//window.draw(pickupArray[universalCounter].rect);
				window.draw(pickupArray[universalCounter].sprite);
				universalCounter++;
			}



			//Draw Projectile
			universalCounter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				projectileArray[universalCounter].update(); // Update projectile
				if (elapsed4.asSeconds() >= 0.2)
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
				enemyArray[universalCounter].update();
				enemyArray[universalCounter].updateMovement();
				enemyArray[universalCounter].wallCollision();
				window.draw(enemyArray[universalCounter].sprite);
				//window.draw(enemyArray[universalCounter].rect);
				//cout << enemyArray[universalCounter].rect.getPosition().x << endl;
				universalCounter++;
			}


			//Update player
			Player1.update();
			Player1.updateMovement();
			//Player1.wallCollision();

			//Draw Player
			//window.draw(Player1.rect);
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
			//cout << health.test<< endl;

			//Draw health
			window.draw(healthBar.sprite);
			window.draw(health.sprite);


			//window.setFramerateLimit(30);//Sets FPS to 60
			window.display();//End current frame
		}
		return;
	}
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



