#include "SFMLView.hpp"
#include "Grid.hpp"
#include "Cell.hpp"
#include "AliveState.hpp"
#include "DeadState.hpp"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <random>
#include <iostream>


SFMLView::SFMLView(unsigned int cellSize, unsigned int margin)
    : m_cellSize(cellSize), m_margin(margin) {
    // La fenêtre sera créée dans init()
}

void SFMLView::init(Grid& grid) {
    int w = grid.getW();
    int h = grid.getH();

    m_grid = &grid;

    unsigned int windowWidth  = m_margin + w * (m_cellSize + m_margin);
    unsigned int windowHeight = m_margin + h * (m_cellSize + m_margin);

    m_window.create(
        sf::VideoMode(windowWidth, windowHeight),
        "Jeu de la vie - SFML"
    );

    m_window.setFramerateLimit(30);
}

void SFMLView::render(Grid& grid) {
    if (!m_window.isOpen())
        return;

    m_window.clear(sf::Color::Black);

    int h = grid.getH();
    int w = grid.getW();

    sf::RectangleShape cellShape(sf::Vector2f(
        static_cast<float>(m_cellSize),
        static_cast<float>(m_cellSize)
    ));

    sf::Vector2u winSize = m_window.getSize();

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Cell& cell = grid.getCell(x, y);

            float px = static_cast<float>(
                m_margin + (x - m_offsetXCells) * (m_cellSize + m_margin)
            );
            float py = static_cast<float>(
                m_margin + (y - m_offsetYCells) * (m_cellSize + m_margin)
            );

            // Si complètement hors écran, on saute
            if (px + m_cellSize < 0 || py + m_cellSize < 0 ||
                px > static_cast<float>(winSize.x) ||
                py > static_cast<float>(winSize.y)) {
                continue;
            }

            cellShape.setPosition(px, py);

            if (cell.isAlive()) {
                cellShape.setFillColor(sf::Color::Green);
            } else {
                cellShape.setFillColor(sf::Color(40, 40, 40));
            }

            m_window.draw(cellShape);
        }
    }

    m_window.display();
}


bool SFMLView::waitNextStep() {
    if (!m_window.isOpen())
        return false;  // on n'avance plus si la fenêtre est fermée

    handleEvents();

    if (m_paused) {
        if (m_stepOnce) {
            m_stepOnce = false;
            sf::sleep(sf::milliseconds(m_delayMs));
            return true;   // une seule itération
        } else {
            sf::sleep(sf::milliseconds(30)); // petit sleep pour pas bouffer 100% CPU
            return false;  // rester sur la même génération
        }
    } else {
        sf::sleep(sf::milliseconds(m_delayMs));
        return true;       // avancer normalement
    }
}



void SFMLView::handleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            // ZOOM +
            if (event.key.code == sf::Keyboard::Add ||
                event.key.code == sf::Keyboard::Equal) {
                if (m_cellSize < m_maxCellSize) {
                    m_cellSize += 2;
                }
            }
            // ZOOM -
            else if (event.key.code == sf::Keyboard::Subtract ||
                    event.key.code == sf::Keyboard::Hyphen) {
                if (m_cellSize > m_minCellSize) {
                    m_cellSize -= 2;
                }
            }
            // VITESSE + (plus lent) avec 'M'
            else if (event.key.code == sf::Keyboard::M) {
                if (m_delayMs < m_maxDelayMs) {
                    m_delayMs += 20;
                }
            }
            // VITESSE - (plus rapide) avec 'P'
            else if (event.key.code == sf::Keyboard::P) {
                if (m_delayMs > m_minDelayMs + 20) {
                    m_delayMs -= 20;
                } else {
                    m_delayMs = m_minDelayMs;
                }
            }
            // PAUSE / PLAY avec espace
            else if (event.key.code == sf::Keyboard::Space) {
                m_paused = !m_paused;
            }
            // UNE ITERATION avec 'N' (seulement utile en pause)
            else if (event.key.code == sf::Keyboard::N) {
                if (m_paused) {
                    m_stepOnce = true;
                }
            }
            // CAMERA : flèches
            else if (event.key.code == sf::Keyboard::Left) {
                m_offsetXCells -= 1;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                m_offsetXCells += 1;
            }
            else if (event.key.code == sf::Keyboard::Up) {
                m_offsetYCells -= 1;
            }
            else if (event.key.code == sf::Keyboard::Down) {
                m_offsetYCells += 1;
            }
            else if (event.key.code == sf::Keyboard::G) {
                int gx, gy;
                if (getMouseGridCoords(gx, gy)) {
                    stampPatternFromFile("patterns/glider.txt", gx, gy);
                }
            }
            else if (event.key.code == sf::Keyboard::C) {
                int gx, gy;
                if (getMouseGridCoords(gx, gy)) {
                    stampPatternFromFile("patterns/canon.txt", gx, gy);
                }
            }
            else if (event.key.code == sf::Keyboard::Q) {
                int gx, gy;
                if (getMouseGridCoords(gx, gy)) {
                    stampPatternFromFile("patterns/double_canon.txt", gx, gy);
                }
            }
            else if (event.key.code == sf::Keyboard::S) {
                int gx, gy;
                if (getMouseGridCoords(gx, gy)) {
                    // Soup aléatoire 10x10 autour de la souris
                    stampRandomSoup(gx, gy, 10, 10, 0.35);
                }
            }

        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && m_grid) {
                int gx, gy;
                if (getMouseGridCoords(gx, gy)) {
                    Cell& cell = m_grid->getCell(gx, gy);
                    if (cell.isAlive()) {
                        cell.setState(std::make_unique<DeadState>());
                    } else {
                        cell.setState(std::make_unique<AliveState>());
                    }
                }
            }
        }
    }
}

bool SFMLView::getMouseGridCoords(int& gridX, int& gridY) const {
    if (!m_grid || !m_window.isOpen()) return false;

    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
    int mx = mousePos.x;
    int my = mousePos.y;

    if (mx < static_cast<int>(m_margin) || my < static_cast<int>(m_margin)) {
        return false;
    }

    int cellSpan = static_cast<int>(m_cellSize + m_margin);

    int localX = (mx - static_cast<int>(m_margin)) / cellSpan;
    int localY = (my - static_cast<int>(m_margin)) / cellSpan;

    gridX = localX + m_offsetXCells;
    gridY = localY + m_offsetYCells;

    if (gridX < 0 || gridX >= m_grid->getW() ||
        gridY < 0 || gridY >= m_grid->getH()) {
        return false;
    }
    return true;
}

void SFMLView::stampPatternFromFile(const std::string& filename, int originX, int originY) {
    if (!m_grid) return;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Impossible d'ouvrir le fichier pattern : " << filename << "\n";
        return;
    }

    int h = 0, w = 0;
    file >> h >> w;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int v = 0;
            file >> v;

            int gx = originX + x;
            int gy = originY + y;

            if (gx < 0 || gx >= m_grid->getW() ||
                gy < 0 || gy >= m_grid->getH()) {
                continue;
            }

            Cell& cell = m_grid->getCell(gx, gy);
            if (v == 1) {
                cell.setState(std::make_unique<AliveState>());
            } else {
                cell.setState(std::make_unique<DeadState>());
            }
        }
    }
}

void SFMLView::stampRandomSoup(int originX, int originY, int width, int height, double density) {
    if (!m_grid) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(density); // proba d'être vivant

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int gx = originX + x;
            int gy = originY + y;

            if (gx < 0 || gx >= m_grid->getW() ||
                gy < 0 || gy >= m_grid->getH()) {
                continue;
            }

            bool alive = dist(gen);
            Cell& cell = m_grid->getCell(gx, gy);

            if (alive) {
                cell.setState(std::make_unique<AliveState>());
            } else {
                cell.setState(std::make_unique<DeadState>());
            }
        }
    }
}

