#include "Level2.hpp" // level header file
#include "GameUI.hpp"
#include "Success.hpp"
using namespace std;
using namespace sf;

void Level2::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		////// mandatory //////
		cout << "in level 2 " << endl;
		Success success;
		LevelFailed levelFailedObj;
		LevelHelper levelhelp;
		GameUI::init();
		Helper::resetEnemyDiedCounter();
		Player::resetMissileCounter();
		Background background;
		Player yuri;
		////// mandatory //////

		bool someone_is_alive;
		unsigned int i;
		vector<Enemy3> first_enemies(3);  // create 2 enemies
		vector<Enemy1> second_enemies(7); // create 3 enemies
		vector<Enemy4> third_enemies(8);

		for (auto& enemy : first_enemies)
		{
			enemy.setStyle(Enemy3::Style::RedRanger);
		}
		for (auto& enemy : second_enemies)
		{
			enemy.setStyle(Enemy1::Style::PurplePunk);
		}
		for (auto& enemy : third_enemies)
		{
			enemy.setStyle(Enemy4::Style::YellowZen);
		}

		while (window.isOpen())
		{
			Helper::resetClock();
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
					exit(0);
				}
				else if (event.type == Event::MouseButtonReleased)
				{
					if (event.mouseButton.button == Mouse::Left)
					{
						yuri.startFiringBullet();
						GameUI::handleClose(window, Mouse::getPosition(window));
						success.handleClose(Mouse::getPosition(window));
						levelFailedObj.handleClose(Mouse::getPosition(window));
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
			yuri.Show(window);
			if (yuri.isDead)
			{
				if (levelFailedObj.isFinishedShowing(window))

				{
					break;
				}
			}

			if (Helper::enemiesDied() == 1)
			{
				if (success.isFinishedShowing(window))
				{
					return;
				}
			}

			GameUI::showPlayerUI(window);

			window.display();
		}
	}
}