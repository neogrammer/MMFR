#include "Tilemap.h"
#include <fstream>
Tilemap::Tilemap(std::string filename, Cfg::Textures texID_)
    : texID{texID_}
    , tileset{}
    , tiles{}
{
    std::ifstream file;
    file.open(filename);

    tileset.clear();
    tiles.clear();
    if (file.is_open())
    { 
        int numTiles, pitch;
        file >> tw >> th >> numTiles >> pitch;
        tileset.reserve(numTiles);
        int rows = numTiles / pitch;
        int cols = pitch;


        for (int ny = 0; ny < rows; ny++)
        {
            for (int nx = 0; nx < cols; nx++)
            {
                //if (y * pitch + x >= numTiles) { break; }
                int num;
                file >> num;
                if (num == 1)
                {
                    tileset.emplace_back(Tile{ sf::IntRect{nx * tw, ny * th, tw, th}, true, texID_ });
                }
                else
                {
                    tileset.emplace_back(Tile{ sf::IntRect{nx * tw, ny * th, tw, th}, false, texID_ });
                }
            }
        }
        std::string mapstr;
        file >> mapstr;
        file.close();
        std::ifstream file2;
        file2.open("Assets/Data/Tilemaps/" + mapstr);
        file2 >> mapW >> mapH;


        tiles.reserve(mapW * mapH);
        for (int ny = 0; ny < mapH; ny++)
        {
            for (int nx = 0; nx < mapW; nx++)
            {
                int num;
                file2 >> num;
                int tilemapPos = ny * mapW + nx;
   
                tiles.push_back(tileset.at(num));
                tiles[tilemapPos].x_ = (float)(nx * tileset.at(0).tw());
                tiles[tilemapPos].y_ = (float)(ny * tileset.at(0).th());
                tiles[tilemapPos].w_ = (float)(tileset.at(0).tw());
                tiles[tilemapPos].h_ = (float)(tileset.at(0).th());
            }
        }

    }
}



Tilemap::~Tilemap()
{
}

std::vector<Tile>& Tilemap::getTiles()
{
    return tiles;
}

std::vector<Tile>& Tilemap::getTileset()
{
    return tileset;
}

Tile Tilemap::copyTilesetTile(int index)
{
    return Tile{ tileset.at(index) };
}

Tile& Tilemap::getTilemapTile(int index)
{
    return tiles[index];
}

void Tilemap::Render(sf::RenderWindow& wnd_)
{
    const auto& center = wnd_.getView().getCenter();
    for (int y = (int)((center.y - 350.f) / 50); y < (int)((center.y + 350.f) / 50); y++)
    {
        if (y >= mapH || y < 0) { continue; }
        for (int x = (int)((center.x - 450.f) / 50); x < (int)((center.x + 450.f) / 50); x++)
        {
            if (x >= mapW || x < 0) { continue; }
            if (y * mapW + x >= mapW * mapH) { continue; }
            int num = y * mapW + x;
            // tile is within the screen boundary, check if it is solid then draw it if it is
            if (tiles[num].getSolid() == true)
            {
                wnd_.draw(*tiles[num].getSprite());
            }
        }
    }
}
