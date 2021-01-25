#include "Level102.hpp" // level header file
using namespace std;
using namespace sf;

void Level102::Show(RenderWindow& window, Event& event)
{
	cout << "in level 102 " << endl;
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	LevelHelper levelhelp;
	Helper::resetEnemyDiedCounter();
	Helper::resetClock();
	Background background;
	Player yuri; // our hero
	bool someone_is_alive;
	unsigned int i;
	vector<Enemy3> first_enemies(3);  // create 2 enemies
	vector<Enemy1> second_enemies(7); // create 3 enemies
	vector<Enemy1> third_enemies(8);

	while (window.isOpen())
	{
		Helper::resetClock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					yuri.startFiringBullet();
				}
			}
		}
		window.clear(Color::Blue);
		background.Show(window);
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			yuri.fireMissile();
		}
		yuri.fireBullet();
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			yuri.moveLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			yuri.moveRight();
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			yuri.moveUp();
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			yuri.moveDown();
		}

		someone_is_alive = false; // আমরা চাচ্ছি প্রথমে ২ টা, তারপর ৩ টা, তারপর ৪ টা enemy একসাথে আসবে ।

		for (auto& this_enemy : first_enemies) // range based for loop + reference operator ফাস্ট হবে ।
		{
			if (this_enemy.isDead == false)
			{
				if (someone_is_alive == false)
					someone_is_alive = true;
				this_enemy.move(300);
				this_enemy.fireBullet(yuri, 4000, 2000, 400);
				this_enemy.fireMissile(yuri, 5000, 1000, 300);
				levelhelp.isHitBody(yuri, this_enemy);
				levelhelp.isHitBullet(yuri, this_enemy);
				levelhelp.isHitMissile(yuri, this_enemy);
				this_enemy.Show(window);
			}
		}

		if (someone_is_alive == false)
		{
			for (i = 0; i < second_enemies.size(); i++)
			{
				if (second_enemies[i].isDead == false)
				{
					if (someone_is_alive == false)
						someone_is_alive = true;
					second_enemies[i].move(300);
					second_enemies[i].fireBullet(yuri, 4000, 2000, 400);
					second_enemies[i].fireMissile(yuri, 5000, 1000, 300);
					levelhelp.isHitBody(yuri, second_enemies[i]);
					levelhelp.isHitBullet(yuri, second_enemies[i]);
					levelhelp.isHitMissile(yuri, second_enemies[i]);
					second_enemies[i].Show(window);
				}
			}
		}

		if (someone_is_alive == false)
		{
			for (i = 0; i < third_enemies.size(); i++)
			{
				if (third_enemies[i].isDead == false)
				{
					if (someone_is_alive == false)
						someone_is_alive = true;
					third_enemies[i].move(300);
					third_enemies[i].fireBullet(yuri, 4000, 2000, 400);
					third_enemies[i].fireMissile(yuri, 5000, 1000, 300);
					levelhelp.isHitBody(yuri, third_enemies[i]);
					levelhelp.isHitBullet(yuri, third_enemies[i]);
					levelhelp.isHitMissile(yuri, third_enemies[i]);
					third_enemies[i].Show(window);
				}
			}
		}

		if (Helper::enemiesDied() == 18)
		{
			return; // show next level
		}
		yuri.Show(window);
		if (yuri.isDead)
			levelFailedObj.Show(window, event); // show level failed
		window.display();
	}
}