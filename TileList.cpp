// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"

TileList::TileList()
{
    // TODO: write this member
}

TileList::~TileList()
{
    delete[] m_elements;
}

void TileList::addTile(Tile tile)
{
    checkResize();
    m_elements[m_size] = tile;
    m_size++;

}

void TileList::drawAll(QGraphicsScene* scene)
{
    for(int i = 0; i < m_size; i++){
        m_elements[i].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y)
{
    int i = m_size-1;
    for(i ; i >= 0; --i){
        if(m_elements[i].contains(x, y)){
            return i;
        }
    }
    return -1;
}

void TileList::raise(int x, int y){
    int indexTop = indexOfTopTile(x, y);
    Tile tempTopTile = m_elements[indexTop];
    if(indexTop != -1){
        for (int i = indexTop; i < m_size; ++i){
            if(i < (m_size-1)){
                m_elements[i] = m_elements[i+1];
            }
            else{
                m_elements[i] = tempTopTile;
            }
        }
    }
}

void TileList::lower(int x, int y)
{
    int indexTop = indexOfTopTile(x, y);
    Tile tempTopTile = m_elements[indexTop];
    if(indexTop != -1){
        for(int i = indexTop; i >= 0; --i){
            if(i != 0){
            m_elements[i] = m_elements[i-1];         //Shift elements right to make room at the top
            }
            else{
                m_elements[i] = tempTopTile;
            }
        }
    }
}

void TileList::remove(int x, int y)
{
    int topTile = indexOfTopTile(x, y);
    if(topTile != -1){
        for (int i = topTile; i < m_size; i++){
                m_elements[i] = m_elements[i+1];
            }
         m_size--;
        }
}

void TileList::removeAll(int x, int y)
{
    for(int i = 0; i < m_size; ++i){
        int indexTop = indexOfTopTile(x, y);
        if(indexTop != -1){
            for(int j = indexTop; j < m_size; ++j){
                m_elements[j] = m_elements[1+j];
            }
        }
    }
}



void TileList::checkResize() {
    if (m_size == m_capacity) {
        // out of space; resize
        Tile* bigDaddy = new Tile[m_capacity * 2];
        for (int i = 0; i < m_size; i++) {
            bigDaddy[i] = m_elements[i];
        }
        delete[] m_elements;   // free old array's memory
        m_elements = bigDaddy;
        m_capacity *= 2;
    }
}
