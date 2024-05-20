#pragma once
#include <algorithm>
#include <string>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;


static int check = 0;
static int r_check = 0;


ref class Enemy {
private:
	double m_x;
	double m_y;
	double m_speed;
	bool m_isGameOver;
public:
	Enemy(double x, double y, double speed) :m_x(x), m_y(y), m_speed(speed) {
		m_isGameOver = false;
	}
	void Draw(Graphics^ g) {
		Bitmap^ img = gcnew Bitmap("enemy.png");
		g->DrawImage(img, (float)(m_x), (float)(m_y));
	}
	void Tick() {
		m_y += m_speed;
	}
	double getX() {
		return m_x;
	}
	double getY() {
		return m_y;
	}
	void setX(double x) {
		m_x = x;
	}
	void setY(double y) {
		m_y = y;
	}
	void battlefieldColision(double width, double length) {
		if (m_y > length) {
			m_isGameOver = true;
		}
	}
	void gameOver() {
		m_speed = 0;
		m_y = -300;
		m_x = -300;
	}
	bool isGameOver() {
		return m_isGameOver;
	}

	void restart() {
		if (r_check == 3)
			r_check = 0;
		m_speed = 2;
		switch (r_check) {
		case 0:
			m_x = rand() % 10 + 1;
			break;
		case 1:
			m_x = rand() % 100 + 80;
			break;
		case 2:
			m_x = rand() % 225 + 180;
			break;
		}
		++r_check;
		m_y = (rand() % 600 + 200) * -1;
		m_isGameOver = false;
	}

};


ref class Player {
private: 
	double m_x;
	double m_y;
	double m_initialX;
	double m_initialY;
	double m_speed;
	bool m_goRight;
	bool m_goLeft;
	bool m_isGameOver;
public:
	Player(double x, double y, double speed) :m_x(x), m_y(y), m_speed(speed)
	{
		m_initialX = x;
		m_initialY = y;
		m_isGameOver = false;
	}
	void Draw(Graphics^ g) {
		Bitmap^ img = gcnew Bitmap("player.png");
		g->DrawImage(img, (float)(m_x), (float)(m_y));
	}
	void Tick() {
		if (m_goLeft == true) {
			m_x -= m_speed;
		}
		if (m_goRight == true) {
			m_x += m_speed;
		}
	}
	double getX() {
		return m_x;
	}
	double getY() {
		return m_y;
	}
	void setY(double y) {
		m_y = y;
	}
	void setGoRight(bool goRight) {
		m_goRight = goRight;
	}
	void setGoLeft(bool goLeft) {
		m_goLeft = goLeft;
	}
	void battlefieldColision(double width, double length) {
		if (m_x > width-110) {
			m_x = width-110;
			m_goRight = false;
		}
		if (m_x < 0) {
			m_x = 0;
			m_goLeft = false;
		}
	}
	void enemyColiison(Enemy^ e) {
		int leftX = std::max(int(m_x), int(e->getX()));
		double rightX = std::min(int(m_x)+80, int(e->getX() + 100));
		double topY = std::max(int(m_y), int(e->getY()));
		double bottomY = std::min(int(m_y) +80, int(e->getY()+100));

		if (leftX < rightX && topY < bottomY) {
			m_isGameOver = true;
		}
	}
	bool isGameOver() {
		return m_isGameOver;
	}
	void gameOver() {
		
		m_y = -300;
		m_x = -300;
		m_speed = 0;
	}
	void restart() {
		m_x = m_initialX;
		m_y = m_initialY;
		m_speed = 3;
		m_isGameOver = false;
	}
};


ref class InterfaceMenu {
private:
	Label^ m_txtScore;
	Label^ m_message;
	int m_score;
public:
	InterfaceMenu(Label^ txtScore, Label^ message) {
		m_score = 0;
		m_txtScore = txtScore;
		m_message = message;
	}
	void outputScore() {
		std::string str;
		str = std::to_string(m_score);
		String^ str2 = gcnew String(str.c_str());
		m_txtScore->Text = str2;
	}
	void IncreaseScore() {
		++m_score;
	}
	void gameOver() {
		std::string str;
		str = "Game Over! Press Enter to start again.";
		String^ str2 = gcnew String(str.c_str());
		m_message->Text = str2;
	}
	int getScore() {
		return m_score;
	}
	void restart() {
		m_score = 0;
		std::string str;
		str = "";
		String^ str2 = gcnew String(str.c_str());
		m_message->Text = str2;
	}

};

ref class Bullet {
private:
	double m_x;
	double m_y;
	double m_speed;
	bool beUsed;
	
public:
	Bullet(double x, double y, double speed) : m_x(x), m_y(y), m_speed(speed) 
	{
		beUsed = false;
	}
	void Draw(Graphics^ g) {
		Bitmap^ img = gcnew Bitmap("bullet.png");
		g->DrawImage(img, (float)(m_x), (float)(m_y));
	}
	void Tick() {
		m_y -= m_speed;
	}
	void enemyColision(Enemy^ e, InterfaceMenu^ m) {
		if (check == 3)
			check = 0;
		int leftX = std::max(int(m_x), int(e->getX()));
		int rightX = std::min(int(m_x) + 5, int(e->getX() + 130));
		int topY = std::max(int(m_y), int(e->getY()));
		int bottomY = std::min(int(m_y) + 10, int(e->getY() + 130));

		if (leftX < rightX && topY < bottomY) {
			switch (check) {
			case 0:
				e->setX(rand() % 10 + 1);
				break;
			case 1:
				e->setX(rand() % 100 + 80);
				break;
			case 2:
				e->setX(rand() % 225 + 180);
				break;
			}
			e->setY((rand() % 600 + 200) * -1);
			m_x = -300;
			m_speed = 0;
			beUsed = true;
			m->IncreaseScore();
			++check;
		}
	}
	void battlefieldColision() {
		if (m_y < 0) {
			m_x = -300;
			m_speed = 0;
			beUsed = true;
		}
	}
	bool getUsed() {
		return beUsed;
	}
	void gameOver() {
		if (beUsed == false) {
			m_x = -300;
			m_y = -300;
			m_speed = 0;
		}
	}

};


ref class Battlefield {
	ref struct Element {
		Enemy^ item;
		Element^ next;
	};
	ref struct ElementBullet {
		Bullet^ item;
		ElementBullet^ next;
	};
private:
	Element^ first;
	double m_width;
	double m_length;
	PictureBox^ m_pb;
	Player^ m_player;
	ElementBullet^ b_first;
	InterfaceMenu^ m_menu;
	bool m_isGameOver;
	bool m_shooting;
public:
	Battlefield(PictureBox^ pb) {
		m_pb = pb;
		m_pb->BackColor = Color::Blue;
		m_length = pb->Height;
		m_width = pb->Width;
		m_isGameOver = false;
		m_shooting = true;
	}
	void Add(Enemy^ enemy) {
		Element^ temp = gcnew Element;
		temp->item = enemy;
		temp->next = first;
		first = temp;
	}
	void Add(Bullet^ bullet) {
			ElementBullet^ temp = gcnew ElementBullet;
			temp->item = bullet;
			temp->next = b_first;
			b_first = temp;
	}
	void Add(Player^ player) {
		m_player = player;
	}
	void Add(InterfaceMenu^ menu) {
		m_menu = menu;
	}
	Player^ getPlayer() {
		return m_player;
	}
	void Draw() {
		Bitmap^ bmp;
		bmp = gcnew Bitmap(m_pb->Width, m_pb->Width);
		Graphics^ g = Graphics::FromImage(bmp);
		g->Clear(m_pb->BackColor);
		Element^ temp = first;
		ElementBullet^ b_temp = b_first;
		m_player->Draw(g);
		while (temp != nullptr) {
			temp->item->Draw(g);
			temp = temp->next;
		}
		while (b_temp != nullptr) {
			if(b_temp->item->getUsed() == false)
			b_temp->item->Draw(g);
			b_temp = b_temp->next;
		}
		m_pb->Image = bmp;
	}
	void Tick() {
		Element^ temp = first;
		ElementBullet^ b_temp = b_first;
		while (temp != nullptr) {
			temp->item->battlefieldColision(m_width, m_length);
			temp->item->Tick();
			m_player->enemyColiison(temp->item);
			temp = temp->next;
		}
		temp = first;
		while (b_temp != nullptr) {
			b_temp->item->Tick();
			b_temp->item->battlefieldColision();
			while (temp != nullptr) {
				b_temp->item->enemyColision(temp->item, m_menu);
				temp = temp->next;
			}
			temp = first;
			b_temp = b_temp->next;
		}
		
		m_menu->outputScore();
		m_player->Tick();
		m_player->battlefieldColision(m_width, m_length);
		
	}
	void gameOver() {
		Element^ temp = first;
		ElementBullet^ b_temp = b_first;
		while (temp != nullptr) {
			if (temp->item->isGameOver() == true) {
				m_isGameOver = true;
			}
			temp = temp->next;
		}
		if (m_player->isGameOver() == true) {
			m_isGameOver = true;
		}
		temp = first;
		if (m_isGameOver) {
			m_menu->gameOver();
			m_player->gameOver();
			while (temp != nullptr) {
				temp->item->gameOver();
				temp = temp->next;
			}
			while (b_temp != nullptr) {
				b_temp->item->gameOver();
				b_temp = b_temp->next;
			}
			
		}
	}
	bool getIsGameOver() {
		return m_isGameOver;
	}
	bool getShooting() {
		return m_shooting;
	}
	void setShooting(bool shooting) {
		m_shooting = shooting;
	}
	void restart() {
		Element^ temp = first;
		if (m_isGameOver == true) {
			m_isGameOver = false;
			m_player->restart();
			m_menu->restart();
			while (temp != nullptr) {
				temp->item->restart();
				temp = temp->next;
			}
		}
	}
};


