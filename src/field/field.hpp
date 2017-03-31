#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "../tileinfo/tileinfo.hpp"
#include "../tile/tile.hpp"
#include "../matrix/matrix.hpp"
#include "../object/object.hpp"
#include "../generate_objects/generateobjects.hpp"
#include "../generate_map/generatemap.hpp"
#include "../do_step/dostep.hpp"


#ifndef HEADER_FIELD_HPP_INCLUDED
#define HEADER_FIELD_HPP_INCLUDED

class Field 
{
private:
    Matrix<Tile>     mMap;
    TileInfo&        mTileInfo;
    // In pixels
    sf::Vector2u mSizePixels;
    sf::RenderWindow mWindow;
    // Массив указателей на объекты с поля
    std::vector< Object* > mObjects;

    GenerateMap&     mGenerateMap;
    GenerateObjects& mGenerateObjects;
    DoStep&          mDoStep;

public:    
    // fSizeTile
    Field(sf::Vector2u sizeTile, GenerateObjects& generateObjects,
          GenerateMap& generateMap, DoStep& doStep,
          TileInfo& tileInfo);
    
    // Деструктор
    ~Field();
    
    sf::RenderWindow& getWindow();

    // Открыто ли привязанное окно
    bool isWindowOpen();
    
    // Активность привязанного окна
    void setActive( bool status );

    // Вывести на W все объекты (вызвать draw(W) для них)
    void draw();

    void drawObjects();

    void drawTiles();
    
    // Вызвать метод display привязанного окна
    void display();
        
    // Функция генерации поля, принимает ссылку на генератор
    void generate();

    // Функция пересчета состояния поля на один игровой шаг
    void doStep();
    
    // Оператор вывода в поток
    friend std::ostream& operator<< (std::ostream& ostr, Field & F) {
        ostr << "Field: (" << F.mSizePixels.x << ", " << F.mSizePixels.y << ")" << std::endl;
        for (auto & iterator: F.mObjects)
            ostr << "      " << (*iterator) << std::endl;
        return ostr;
    }
};

#endif
