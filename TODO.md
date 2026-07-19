### MVP

#### Architecture

- Game
  - Handles the Flow of the Overall Game, what UI to display, and the Roster of Units the Player has Available.
  - GAME_STATE {MAINMENU, CITY, ENCOUNTER}
    - Game handles the current highest level part of a scene, which all other systems listen to.
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
  - 