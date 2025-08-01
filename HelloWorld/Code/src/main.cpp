#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

int main(int argc, char* argv[])
{
	constexpr int windowWidth = 800;
	constexpr int windowHeight = 600;
	constexpr int buttonWidth = 80;
	constexpr int buttonHeight = 60;
	constexpr int buttonPosX = static_cast<int>(static_cast<float>(windowWidth) * 0.5f) - static_cast<int>(static_cast<float>(buttonWidth) * 0.5f);
	constexpr int buttonPosY = static_cast<int>(static_cast<float>(windowHeight) * 0.5f) - static_cast<int>(static_cast<float>(buttonHeight) * 0.5f);

	QApplication app(argc, argv);

	QWidget window;
	window.setFixedSize(windowWidth, windowHeight);

	QPushButton* button = new QPushButton("Click me!", &window);
	button->setGeometry(buttonPosX, buttonPosY, buttonWidth, buttonHeight);

	QObject::connect(button, &QPushButton::clicked, [button]()
		{
			button->setText("Hello, World!");
		});

	window.show();
	return app.exec();
}