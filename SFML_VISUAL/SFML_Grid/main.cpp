#include <SFML/Graphics.hpp>



int main()
{
	int length = 10000;
	sf::Image image;
	sf::Color gridColor(79, 86, 71);
;	image.create(length, length, sf::Color(60, 66, 54));
	
	for (int x = 0; x < length; x += 50)
		for (int y = 0; y < length; y++)
		{
			image.setPixel(x, y, gridColor);
			image.setPixel(y, x, gridColor);
		}
			
	if (!image.saveToFile("gridImage.png"))
		return -1;
		

	return EXIT_SUCCESS;
}