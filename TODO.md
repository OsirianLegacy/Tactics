## MVP

### Architecture

- Game
  - Handles the Flow of the Overall Game, what UI to display, and the Roster of Units the Player has Available.
  - GAME_STATE {MENU, CITY, ENCOUNTER}
    - Game handles the current highest part of a scene, which all other systems listen to.
    - Game holds all pertinent Data, and systems reach into game to grab that data.
    - UI Controls Game based on button presses. 

- Combat
  - Handles the Flow of the current Combat via phases.
    - COMBAT_STATE {INITIALIZE, DEPLOY, SPAWN, NEW ROUND, PLAYER, ENEMY, END ROUND}
    - UI & AI Controls Combat Flow via button presses & AI decisions.
    
- Action
  - Handles the Validation and Execution of every action in Combat
  - The UI Manager & AI Manager send requests to Action for verification and execution. Units are dumb stat holders.
  - ACTION_STATE {RANGE, TARGET, DISPLAY, CONFIRM, EXECUTE, CLEAR}
  - Action States always execute in sequence. Even ending a turn should go through each step.
  - Action expects an ActionRequest Structure every time an action is received by UI, or AI

- UI
  - Handles displaying the proper GAME_STATE as well as UI_STATE as listed below.
  - UI_STATE {IDLE, LOAD, SAVE, ROSTER, MISSION, TURN, TARGET, CONFIRM}
  - Gets Mouse Position every tick from Player, and checks if its position overlaps the position of any buttons.
  - Uses Widget Structures to draw, send ActionRequests, and Change the COMBAT & GAME STATE.

- Player
  - Handles Input detections from Mouse, Keyboard, and Controller.
  - Tells the Grid where the mouse is on Tick, if its Position is a Valid Cell, the Grid Sets Hovered Cell & Visuals.
  - Tell the UI and the Grid when player presses a keyboard or controller button, or clicks L/R MB
  - UI and Grid responds to these events.
  - Will need a Player Input Structure that gets sent to UI and Grid.

- Grid
  - Referenced by Combat, Action, and Player. 
  - Handles Grid Generation, Grid Visuals, Pathfinding, and Cell Click/Hover detection.
  - Dummy Class that does nothing on its own, and requires another class to query it and update its values.

- Unit
  - Units are built from a Definition of Base Values and turned into Runtime Data during Combat.
  - Units are dumb, and simply hold and manipulate their Data.
  - Units don't act, the AI or the Player Acts. However Units have States as listed below.
  - UNIT_STATE {IDLE, THINKING, MOVING, ATTACKING, DEAD}

- AI
  - Handles the deduction of possible actions for each Enemy Unit in Combat on Tick.
  - Displays the Intents of each Enemy in top Right.
  - As Player takes actions during their turn Intents Update to reflect what the Enemy will Do.

- Debug
  - Handles all Debugging in the game, including imGUI debug Windows. 

# TODO

## Sprint 1 - Project Foundation and Game Loop

Goal: Create the minimum project structure needed to open a window, update game state, and draw a placeholder screen.

- [x] Add a shared `Types` or `Core` header for common enums and small data structures.
- [x] Create `GameState` enum with `MENU`, `CITY`, and `ENCOUNTER`.
- [x] Create a `Game` class or module that owns the current `GameState`.
- [x] Add a `SetGameState(GameState nextState)` function.
- [ ] Add a simple game initialization function.
- [X] Wire `main.cpp` to initialize raylib, create the game object, run update/draw each frame, and shut down cleanly.
- [X] Draw different placeholder text or background color for each `GameState`.
- [X] Add New Game, Load Game, Options Buttons in MainMenu.
- [ ] Create Options Panel to Exit the Game, and Change Resolution, so I can test Resolutions in-game. Should just change Render Scale. Add Fullscreen Toggle.
- [X] Add Buttons for Entering the Tavern, Clinic, Departing, and Options to City.
- [ ] Add basic debug logging for game state transitions.
- [ ] Create Close Widget for closing menu panels.
- [ ] 