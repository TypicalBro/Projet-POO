code mermaid.live diagramme de classe 

```
classDiagram
    direction LR

    class Game {
        - Grid* grid
        - IRule* rule
        - IView* view
        - unsigned int maxIterations
        - unsigned int currentIteration
        + Game(IRule* rule, IView* view, unsigned int maxIter = 100)
        + void loadFromFile(const std::string& path)
        + void run()
        + void step()
        + bool isStable() const
    }

    class Grid {
        - unsigned int width
        - unsigned int height
        - std::vector<std::vector<Cell>> cells
        - std::vector<std::vector<ICellState*>> nextStates
        + Grid(unsigned int w, unsigned int h)
        + unsigned int getWidth() const
        + unsigned int getHeight() const
        + Cell& getCell(unsigned int x, unsigned int y)
        + const Cell& getCell(unsigned int x, unsigned int y) const
        + unsigned int countAliveNeighbors(unsigned int x, unsigned int y) const
        + void computeNextStates(IRule& rule)
        + bool applyNextStates()
    }

    class Cell {
        - unsigned int x
        - unsigned int y
        - ICellState* state
        + Cell(unsigned int x, unsigned int y, ICellState* initialState)
        + unsigned int getX() const
        + unsigned int getY() const
        + bool isAlive() const
        + void setState(ICellState* newState)
        + ICellState* getState() const
    }

    class ICellState {
        <<interface>>
        + bool isAlive() const
        + ICellState* clone() const
    }

    class AliveState {
        + bool isAlive() const
        + ICellState* clone() const
    }

    class DeadState {
        + bool isAlive() const
        + ICellState* clone() const
    }

    class IRule {
        <<interface>>
        + ICellState* computeNextState(const Cell& cell, unsigned int aliveNeighbors) const
    }

    class ConwayRule {
        + ICellState* computeNextState(const Cell& cell, unsigned int aliveNeighbors) const
    }

    class IView {
        <<interface>>
        + void initialize(Grid& grid)
        + void render(const Grid& grid)
        + void waitNextStep()
    }

    class ConsoleView {
        - std::string outputFolder
        + ConsoleView(const std::string& outputFolder)
        + void initialize(Grid& grid)
        + void render(const Grid& grid)
        + void waitNextStep()
    }

    class SFMLView {
        - unsigned int cellSize
        - float stepDurationSeconds
        - sf::RenderWindow* window
        + SFMLView(unsigned int cellSize, float stepDuration)
        + void initialize(Grid& grid)
        + void render(const Grid& grid)
        + void waitNextStep()
    }

    class FileLoader {
        + static Grid* load(const std::string& path)
        + static void save(const Grid& grid, const std::string& directory, unsigned int iterationIndex)
    }

    %% Relations
    Game --> Grid : utilise
    Game --> IRule : utilise
    Game --> IView : utilise

    Grid "1" o-- "many" Cell
    Cell --> ICellState
    ICellState <|-- AliveState
    ICellState <|-- DeadState

    IRule <|-- ConwayRule

    IView <|-- ConsoleView
    IView <|-- SFMLView

    Game ..> FileLoader : lit/écrit fichiers


```

code mermaid.live diagramme de sequence

```
sequenceDiagram
    actor User
    participant main
    participant Game
    participant FileLoader
    participant Grid
    participant IRule as Rule
    participant IView as View

    User->>main: ./game_of_life input.txt --mode=console
    main->>Game: new Game(rule, view, maxIter)
    main->>Game: loadFromFile("input.txt")
    Game->>FileLoader: load("input.txt")
    FileLoader-->>Game: Grid*

    main->>Game: run()

    loop while !isStable() && currentIteration < maxIterations
        Game->>View: initialize(grid) (première fois seulement)
        Game->>View: render(grid)

        Game->>Grid: computeNextStates(rule)
        Grid->>Rule: computeNextState(cell, aliveNeighbors)
        Rule-->>Grid: nextState
        Note over Grid: Stocke les nextStates pour toutes les cellules

        Game->>Grid: applyNextStates()
        Grid-->>Game: bool changed

        alt pas de changement
            Game->>Game: set isStable = true
        end

        Game->>View: waitNextStep()
    end

    Game-->>main: terminaison

```

Code mermaid.live diagramme d'activite

```
flowchart TD
    A([Start])
    B["Lire les arguments :\nchemin fichier, mode, maxIterations"]
    C["Charger la grille\n(FileLoader::load)"]
    D["Créer la règle\n(ConwayRule)"]
    E["Créer la vue\n(ConsoleView ou SFMLView)"]
    F["Créer Game(rule, view, maxIter)"]
    G["iteration = 0"]
    H["isStable = false"]

    A --> B
    B --> C
    C --> D
    D --> E
    E --> F
    F --> G
    G --> H

    H --> I{"Grille stable\nOU\niteration >= maxIterations ?"}
    I -- "Oui" --> Z([Fin])
    I -- "Non" --> J["Si première itération :\nview.initialize(grid)"]
    J --> K["view.render(grid)"]
    K --> L["grid.computeNextStates(rule)"]
    L --> M["changed = grid.applyNextStates()"]

    M --> N{"changed == false ?"}
    N -- "Oui" --> O["isStable = true"]
    N -- "Non" --> P["isStable = false"]

    O --> Q["iteration++"]
    P --> Q
    Q --> R["view.waitNextStep()\n(console : rien,\nGUI : timer)"]
    R --> H

```
