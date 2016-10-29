
#include <SPI.h>
#include <EEPROM.h>

#include <Gamebuino.h>

//#include "ArduboyCustom.h"
#include "Globals.h"
#include "GUI.h"
#include "StarField.h"
#include "Ship.h"
#include "Map.h"
#include "Text.h"

#define Debug 0

// To decompile the elf and sort by function size:
// avr-nm --size-sort -C -r ./VoyageHome.ino.elf > ~/output.txt

StarField* _StarField;

void setup() {
  #if Debug
    Serial.begin(9600);
  #endif
  MilliPerFrame = 1000.0f / 60.0f;

  //arduboy.start();
  arduboy.begin();
  //arduboy.display();
  arduboy.titleScreen();
  arduboy.battery.show = false;
  //arduboy.initRandomSeed();
  arduboy.pickRandomSeed();

#if !Debug
  _StarField = new StarField();
#endif

  MapUpperBounds = new Vector2d(-32, -128);
  MapLowerBounds = new Vector2d(512, 128);

  TextManager = new Text();

#if !Debug
  CreateStatusSelectionArrow();

  CreateCombatSelectionArrow();
#endif

  ChangeGameState( TitleLoop );
  MenuWaitTime = 15;

  // Order is important to prevent Heap Fragmentation
  PlayerShip = new Ship();
  Ship::SetupShip( PlayerShip );
  TimeUntilNextRepair = RepairTime;
  InitializePlanetsArray();
  NewMap();
}

void loop()
{
  //if ( millis() < (LastUpdateTime + MilliPerFrame) ) return;
  //DeltaTime = ( millis() - LastUpdateTime ) / 1000.0f;
  //LastUpdateTime = millis();
  if(arduboy.update()){

  //Why do so many of these innocuous functions make it CRASH
  //So apparently putting it in init made it choke and die.  Ok...
  //arduboy.display.fillScreen(BLACK);
  arduboy.display.setColor(BLACK);
  arduboy.display.fillRect(0,0,84,48);
  //arduboy.display.fillScreen(BLACK);  //BUT THIS METHOD STILL CAUSES A CRASH WHY
  arduboy.display.setColor(WHITE);
  //arduboy.display.setColor(WHITE);

  DeltaTime = 0.05;//Seconds per frame
  //By default persistence is false for Gamebuino
  //arduboy.clearDisplay();
  GetInput();
  
  switch ( GameState )
  {
    case TitleLoop:
      _StarField->Draw();
      //Text::DisplayTextClear( TitleScreen2, 6, 56, true, false );
      Text::DisplayTextClear( TitleScreen2, 0, 40, true, false );
      //if ( TextManager->DisplayTextOverTime( TitleScreen, 42, 24 ) && BButton )
      if ( TextManager->DisplayTextOverTime( TitleScreen, 84/2-24, 48/2-8 ) && BButton )
        ChangeGameState( Prologue );
    break;
    case Prologue:
      PrologueLoop();
    break;
    case Map:
      PlayerShip->Update();
      PlayerShip->DrawOnMap();

      /*
      //Debug text
      arduboy.display.cursorX = 0;
      arduboy.display.cursorY = 0;
      arduboy.display.print(PlayerShip->MapPosition->x);
      arduboy.display.print(" ");
      arduboy.display.println(PlayerShip->MapPosition->y);
      /*arduboy.display.println(DPad);
      arduboy.display.println(PlayerShip->Velocity->x);
      arduboy.display.println(PlayerShip->Velocity->y);
      arduboy.display.println(PlayerShip->ShipRotation);
      */
      
      #if !Debug
      _StarField->Move(PlayerShip->GetVelocity() * -1.0f);
      _StarField->Draw();
      #endif
      
      MapLoop();

      if ( StatusUpdateAvailable )
      {
        Text::DisplayTextClear( Status_Update, 0, 6, StatusUpdateFromProgMem, true );
        StatusUpdateTime -= 1;
        StatusUpdateAvailable = StatusUpdateTime > 0;
      }
      ClockUpdate( true );

      if ( CanHail )
      {
        Text::DisplayTextClear( Hail, 0, 40, true, false );
        if ( BButton )
        {
          ChangeGameState( Encounter );
          return;
        }
      }
      else if ( PlayerShip->Fuel >= 3 )
      {
        Text::DisplayText( StatusHelp3, 0, 40, true );
        if ( DPad == Up && BButton )
        {
          ChangeGameState( Warping );
        }
      }
    break;
    case Status:
      ShipStatusLoop();
    break;
    case Encounter:
      _StarField->Draw();
      PlayerShip->DrawOnMap();
      DrawMap();
      EncouterUpdate();
    break;
    case GameOver:
      GameOverLoop( 1 );
    break;
    case TimeUp:
      GameOverLoop( 2 );
    break;
    case Reset:
      StatusUpdateAvailable = false;
      StatusUpdateTime = 0;
      Status_Update = NULL;
      CanHail = false;
      LatestPlanetEncountered = NULL;
      ResetPlayer();
      NewMap();
      ChangeGameState( TitleLoop );
      minutes = 9;
      seconds = 59.99f;
    break;
    case Warping:
      _StarField->Move(Vector2d(-60,0));
      _StarField->Draw();
      PlayerShip->DrawOnMap();
      WaitTime -= 1;
      if ( WaitTime <= 0 ) 
      {
        NextSector();
        if ( GameState == WinGame) return;
        
        ChangeGameState( Map );
        SetupSectorReachedText();
      }
    break;
    case WinGame:
      WinGameLoop();
    break;
  }

  }

  //arduboy.display();
}

void GetInput()
{
  int DPadDirection = 8;

  //typedef enum { Up, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft, None } Direction;
  if ( arduboy.buttons.repeat( BTN_UP, 1 ) )
      DPadDirection = 0;
  if ( arduboy.buttons.repeat( BTN_DOWN, 1 ) )
      DPadDirection = 4;
  if ( arduboy.buttons.repeat( BTN_LEFT, 1 ) )
  { 
    if ( DPadDirection == 0 )
      DPadDirection = 7;
    else if ( DPadDirection == 4 )
      DPadDirection = 5;
    else
      DPadDirection = 6;
  }
  if ( arduboy.buttons.repeat( BTN_RIGHT, 1 ) )
  {
    if ( DPadDirection == 0 )
      DPadDirection = 1;
    else if ( DPadDirection == 4 )
      DPadDirection = 3;
    else
      DPadDirection = 2;
  }
  DPad = static_cast<Direction>( DPadDirection );

  //
  //  Button Input
  //
  AButton = false;
  BButton = false;

  if ( newButtonInputAllowed == false && ( !arduboy.buttons.repeat( BTN_B, 1 ) && !arduboy.buttons.repeat( BTN_A, 1 ) ) )
  {
    newButtonInputAllowed = true;
  }

  if ( arduboy.buttons.repeat( BTN_A, 1 ) && newButtonInputAllowed )
  {
    newButtonInputAllowed = false;
    AButton = true;
  }
  if ( arduboy.buttons.repeat( BTN_B, 1 ) && newButtonInputAllowed )
  {
    newButtonInputAllowed = false;
    BButton = true;
  }
}

void CreateStatusSelectionArrow()
{
  OverviewLocations = new Vector2d*[6];
  OverviewLocations[0] = new Vector2d( 0, -2 );  // Ship Systems
  OverviewLocations[1] = new Vector2d( 0, 4 );  // Ship Hull
  OverviewLocations[2] = new Vector2d( 0, 10 );  // Ship Engines
  OverviewLocations[3] = new Vector2d( 0, 16 );  // Crew
  OverviewLocations[4] = new Vector2d( 0, 22 );  // Fuel
  OverviewLocations[5] = new Vector2d( 0, 28 );  // Food

  RepairSelectionArrow = new SelectionArrow( OverviewLocations, 6 );
  CurrentSelectionArrow = RepairSelectionArrow;
}

void CreateCombatSelectionArrow()
{
  CombatLocations = new Vector2d*[3];
  CombatLocations[0] = new Vector2d( 2, 25 );
  CombatLocations[1] = new Vector2d( 2, 32 );
  CombatLocations[2] = new Vector2d( 2, 39 );
  CombatSelectionArrow = new SelectionArrow( CombatLocations, 3 );
}

void ChangeGameState( State newState )
{
  PreviousGameState = GameState;
  switch ( newState )
  {
    case TitleLoop:
      CurrentSector = 1;
      TextManager->NewDisplayTextOverTime();
    break;
    case Prologue:
      SequenceStage = 1;
      TextManager->NewDisplayTextOverTime();
    break;
    case Map:
    break;
    case Status:
      Text::ConvertIntToChar( PlayerShip->Crew, PlayerShip->crewCharArray );
      Text::ConvertIntToChar( PlayerShip->Max_Crew, PlayerShip->maxCrewCharArray );
      Text::ConvertIntToChar( PlayerShip->Fuel, PlayerShip->fuelCharArray );
    break;
    case Encounter:
      SetupEncounter();
    break;
    case GameOver:
      PlayerShip->IsAlive = false;
      TextManager->NewDisplayTextOverTime();
      SequenceStage = 1;
    break;
    case TimeUp:
      PlayerShip->IsAlive = false;
      TextManager->NewDisplayTextOverTime();
      SequenceStage = 1;
    case Reset:
    break;
    case Warping:
      PlayerShip->ShipRotation = 90;
      PlayerShip->Velocity->x = 2;
      PlayerShip->Velocity->y = 0;
      PlayerShip->PlayerUpdate();
      PlayerShip->Fuel -= 3;
      WaitTime = 240; // 240 frames
    break;
    case WinGame:
      SequenceStage = 1;
      TextManager->NewDisplayTextOverTime();
    break;
  }

  GameState = newState;
}

void PrologueLoop()
{ 
  switch ( SequenceStage )
  {
    case 1:
      if ( TextManager->DisplayTextOverTimeClear( PrologueText1, -2, -2 ) || BButton )
        { SequenceStage++; TextManager->NewDisplayTextOverTime(); }
    break;
    case 2:
      
      if ( TextManager->DisplayTextOverTimeClear( PrologueText2, -2, 22 ) || BButton )
        SequenceStage++;
      Text::DisplayText( PrologueText1, 0, 0, true );
    break;
    case 3:
      Text::DisplayText( PrologueText1, 0, 0, true );
      Text::DisplayText( PrologueText2, 0, 24, true );
      if ( BButton )
       ChangeGameState(Map);
     break;
  }
}

void ShipStatusLoop()
{
  if ( DPad == None && AcceptMenuInput == false )
    AcceptMenuInput = true;

  if ( AcceptMenuInput )
  {
    if ( DPad == Up )
    {
      CurrentSelectionArrow->SelectionMoveUp();
      AcceptMenuInput = false;
    }
    else if ( DPad == Down )
    {
      CurrentSelectionArrow->SelectionMoveDown();
      AcceptMenuInput = false;
    }
    // Status Menu
    if ( AButton )
    {
      ChangeGameState( PreviousGameState );
    }
    // Lock Selection
    if ( BButton )
    {
    }
  }

  DrawShipStatusScreen();
  CurrentSelectionArrow->Draw();
}

void DrawShipStatusScreen()
{
  int StatusBarX = 56;
  int TextXPos = 10;

  //Text::DisplayText(ShipStatus, 42, 0, true);
  Text::DisplayText(TCrew, TextXPos, 0, true);
  Text::DisplayText(THull, TextXPos, 6, true);
  Text::DisplayText(TWeapons, TextXPos, 12, true);
  Text::DisplayText(TShields, TextXPos, 18, true);
  Text::DisplayText(TEngines, TextXPos, 24, true);
  Text::DisplayText(TFuel, TextXPos, 30, true);

  if ( RepairTarget != NoTarget && StatusBlinkTime > 30)
  {
    arduboy.display.setColor(BLACK);
    arduboy.display.fillRect( TextXPos, 0 + 6 * RepairTarget, 40, 6 );
    arduboy.display.setColor(WHITE);
  }
  else if (StatusBlinkTime < 0)
    StatusBlinkTime = 60;
  StatusBlinkTime -= 1;
      
  
  //    DrawStatusBar( int x, int y, int length, int height, float fill )
  // 27,600 -> 27,322 ...wow  Just removing the array reference with the arithmetic offset  "OverviewLocation[0].y + 2"
  Text::DisplayText( PlayerShip->crewCharArray, 56, 0, false);
  Text::DisplayText( "/", 70, 0, false );
  Text::DisplayText( PlayerShip->maxCrewCharArray, 76, 0, false );

  arduboy.display.drawRoundRect( StatusBarX, 6, PlayerShip->Max_Hull+2, 4, 2);
  arduboy.display.fillRoundRect( StatusBarX, 6, PlayerShip->HP_Hull+2, 4, 2);
  arduboy.display.drawRoundRect( StatusBarX, 12, PlayerShip->Max_Weapons+2, 4, 2);
  arduboy.display.fillRoundRect( StatusBarX, 12, PlayerShip->HP_Weapons+2, 4, 2);
  arduboy.display.drawRoundRect( StatusBarX, 18, PlayerShip->Max_Shields+2, 4, 2);
  arduboy.display.fillRoundRect( StatusBarX, 18, PlayerShip->HP_Shields+2, 4, 2);
  arduboy.display.drawRoundRect( StatusBarX, 24, PlayerShip->Max_Engine+2, 4, 2);
  arduboy.display.fillRoundRect( StatusBarX, 24, PlayerShip->HP_Engine+2, 4, 2);
  //DrawStatusBar( StatusBarX, 6, PlayerShip->Max_Hull, 4, 100 * PlayerShip->HP_Hull / PlayerShip->Max_Hull );
  //DrawStatusBar( StatusBarX, 12, PlayerShip->Max_Weapons, 4, 100 * PlayerShip->HP_Weapons / PlayerShip->Max_Weapons );
  //DrawStatusBar( StatusBarX, 18, PlayerShip->Max_Shields, 4, 100 * PlayerShip->HP_Shields / PlayerShip->Max_Shields );
  //DrawStatusBar( StatusBarX, 24, PlayerShip->Max_Engine, 4, 100 * PlayerShip->HP_Engine / PlayerShip->Max_Engine );

  Text::DisplayText( PlayerShip->fuelCharArray, StatusBarX, 30, false );

  if ( PreviousGameState == Map )
  {
    if ( CurrentSelectionArrow->Position == 0 )
    {
      Text::DisplayText( StatusHelp2, 0, 42, true );
      if (BButton)  // Triage
      {
         RepairTarget = static_cast<SystemTarget>( CurrentSelectionArrow->Position );
      }
    }
    if ( CurrentSelectionArrow->Position > 0 && CurrentSelectionArrow->Position <= 4 )
    {
      Text::DisplayText( StatusHelp, 0, 42, true );
      if (BButton)  // Repair
      {
        RepairTarget = static_cast<SystemTarget>( CurrentSelectionArrow->Position );
      }
    }
    else if ( CurrentSelectionArrow->Position == 5 )
    {
      Text::DisplayText( StatusHelp4, 0, 42, true );
    }
  }
  else if ( PreviousGameState == Encounter )
  {
    if ( CurrentSelectionArrow->Position > 0 && CurrentSelectionArrow->Position <= 4 )
    {
      Text::DisplayText( SpendEmergencyRepairs, 0, 36, true );
      if (BButton && BattleRepairs > 0)  // Repair
      {
        RepairTarget = static_cast<SystemTarget>( CurrentSelectionArrow->Position );
        int randomRepairs = random(2, 6);
        while ( randomRepairs > 0 )
        {
          PlayerShip->RepairSystem();
          randomRepairs--;
        }
        BattleRepairs--;
      }
    }

    // Bubbles
    if ( BattleRepairsMax > 2 )
      arduboy.display.drawBitmap(84, 42, Bubble_Empty_8_8);
    if ( BattleRepairsMax > 1 )
      arduboy.display.drawBitmap(78, 42, Bubble_Empty_8_8);
    if ( BattleRepairsMax > 0 )
      arduboy.display.drawBitmap(72, 42, Bubble_Empty_8_8);
    
    Text::DisplayText( EmergencyRepairs, 0, 42, true );
    
    if ( BattleRepairs > 2 )
      arduboy.display.drawBitmap(84, 42, Bubble_8_8);
    if ( BattleRepairs > 1 )
      arduboy.display.drawBitmap(78, 42, Bubble_8_8);
    if ( BattleRepairs > 0 )
      arduboy.display.drawBitmap(72, 42, Bubble_8_8);//82 originally
  }
}

void SetupEncounter()
{
  // For if we visit the status screen from within combat, we don't want to reset up the encounter
  if ( PreviousGameState == Status ) return;
  
  SequenceStage = 1;
  RunningAway = false;
  
  if ( LatestPlanetEncountered->Alignment < 0 )
  {
    Comm_A_1 = (char *) Negative_Response[ random(0, 3) ];
  }
  else if ( LatestPlanetEncountered->Alignment == 0 )
  {
    Comm_A_1 = (char *) Neutral_Response[ random(0, 5) ];
  }
  else if ( LatestPlanetEncountered->Alignment > 0 )
  {
    Comm_A_1 = (char *) Positive_Response[ random(0, 3) ];
  }

  Cmd_Atk = (char *) Engage_Combat[random(0, 3)];
  Cmd_Repair = (char *) Repair_Combat[random(0, 3)];
  Cmd_Flee = (char *) Flee_Combat[random(0, 3)];

  PlayerShip->CalculateBattleRepairs();
}

void EncouterUpdate()
{
  int randomInt;
  int index = 0;
  int nextSequence = SequenceStage;
  
  switch ( SequenceStage )
  {
    case 1: // Intro
      if ( TextManager->DisplayTextOverTime( Comm_A_1, 0, 0 ) && BButton )
      {
          TextManager->NewDisplayTextOverTime();
        
          if ( LatestPlanetEncountered->Alignment < 0 )
            nextSequence = 3;
          else if ( LatestPlanetEncountered->Alignment == 0 )
            nextSequence = 7;
          else
            nextSequence = 8;
      }
      break;
    
    case 3: // Combat Choice
      DrawCombatScreen( true );
      
      if ( BButton )
      {
        nextSequence = 4 + CombatSelectionArrow->Position;
      }
    break;
        
    case 4: // Combat Calc
    {
      DrawCombatScreen( false );
      index = 0;

      CombatPlanetDamage = PlayerShip->HP_Weapons + (int) ( random( - (PlayerShip->HP_Weapons * 0.2f ), ( PlayerShip->HP_Weapons * 0.2f ) ) );
      CombatPlanetDamage = max( CombatPlanetDamage, 1 );
      CombatShipShieldDamage = LatestPlanetEncountered->Attack;// + (int) ( random( - (LatestPlanetEncountered->Attack * 0.1f), ( LatestPlanetEncountered->Attack * 0.1f ) ) );
      CombatShipShieldDamage = max( CombatShipShieldDamage, 1 );
      
      CombatPlanetDef = LatestPlanetEncountered->Defense - CombatPlanetDamage;
      
      if ( CombatPlanetDef <= 0 && RunningAway == false )
      {
        Combat_Result = (char *) Victory[ random( 0, 2 ) ];
        TextManager->NewDisplayTextOverTime();
        nextSequence = 15;
        break;
      }
      else
      {
        if (!RunningAway)
        {
          index += Text::CopyIntoBuffer(CombatTakeDamage4, index, 12);
          Text::ConvertIntToChar(CombatPlanetDamage, typeBuffer, index);
          index++;
          int CombatPlanetDamageCopy = CombatPlanetDamage;
          for(; CombatPlanetDamageCopy /= 10; index++);
  
          index += Text::CopyIntoBuffer(CombatTakeDamage2, index, 9);
        }
      }
      
      if ( CombatShipShieldDamage >= PlayerShip->HP_Shields )
      {
        CombatShipDamage = CombatShipShieldDamage - PlayerShip->HP_Shields;

        // Shields Down
        index += Text::CopyIntoBuffer(ShieldsDown, index, 18);

        // Ship Damage
        index += Text::CopyIntoBuffer(CombatTakeDamage1, index, 12);
        Text::ConvertIntToChar(CombatShipDamage, typeBuffer, index);

        index++;
        int CombatShipDamageCopy = CombatShipDamage;
        for(; CombatShipDamageCopy /= 10; index++);

        index += Text::CopyIntoBuffer(CombatTakeDamage2, index, 9);
        SystemDamaged = PlayerShip->TakeDamage( 0 );
        switch ( SystemDamaged )
        {
          case Crew:
            index += Text::CopyIntoBuffer(DamageReportCrew, index, 27);
          break;
          case Hull:
            index += Text::CopyIntoBuffer(DamageReportHull, index, 21);
          break;
          case Weapons:
            index += Text::CopyIntoBuffer(DamageReportWeapons, index, 29);
          break;
          case Shields:
            index += Text::CopyIntoBuffer(DamageReportShields, index, 22);
          break;
          case Engines:
            index += Text::CopyIntoBuffer(DamageReportEngines, index, 24);
          break;
        }
        typeBuffer[index] = '\0';
      }
      else
      {
        index += Text::CopyIntoBuffer(CombatTakeDamage3, index, 17);;
        
        Text::ConvertIntToChar(CombatShipShieldDamage, typeBuffer, index);

        // Optimization 27,288 -> 27,264
        index++;
        int CombatShipDamageCopy = CombatShipDamage;
        for(; CombatShipDamageCopy /= 10; index++);

        index += Text::CopyIntoBuffer(CombatTakeDamage2, index, 9);
        index += Text::CopyIntoBuffer(ShieldsHolding, index, 18);
        typeBuffer[index] = '\0';    
      }
      MenuWaitTime = 15;
      nextSequence = 9;
    }
    break;
    
    case 5: // Status Screen
      nextSequence = 3;
      ChangeGameState(Status);
    break;

    case 6: // Run Away
      nextSequence = 4;
      RunningAway = true;
    break;

    case 7: // Neutral
      LatestPlanetEncountered->Contacted = true;
      CanHail = false;
      ChangeGameState( Map );
    break;

    case 8: // Positive
      LatestPlanetEncountered->Contacted = true;
      GenerateReward( LatestPlanetEncountered->Prize );
      TextManager->NewDisplayTextOverTime();
      nextSequence = 17;
    break;
    
    case 9: // Print Damage
      DrawCombatScreen( false );
      Text::DisplayTextClear( typeBuffer, 0, 21, false, true );
      MenuWaitTime -= 1;
      if ( MenuWaitTime <= 0 && BButton )
      {
        LatestPlanetEncountered->Defense = CombatPlanetDef;
        PlayerShip->HP_Shields = max( PlayerShip->HP_Shields - CombatShipShieldDamage, 0 );
        if ( PlayerShip->HP_Shields <= 0 )
          PlayerShip->TakeDamage(CombatShipDamage, SystemDamaged);
        
        if ( PlayerShip->HP_Hull <= 0 )
        {
          nextSequence = 18;
          break;
        }
        else if ( !RunningAway )
          nextSequence = 3; // Back to combat
        else
          nextSequence = 16;
      }
    break;
    
    case 15: // Success
      
      if ( TextManager->DisplayTextOverTime( Combat_Result, 0, 30 ) )
      {
        if ( BButton )
        {
          GenerateReward( LatestPlanetEncountered->Prize );
          LatestPlanetEncountered->Contacted = true;
          TextManager->NewDisplayTextOverTime();
          nextSequence = 17;
        }
      }
    break;
    case 16: // Ran Away
      ChangeGameState( Map );
    break;
    case 17: // Result
      Text::DisplayTextClear( typeBuffer, 0, 30, false, true );
      if ( BButton )
      {
        CanHail = false;
        ChangeGameState( Map );
      }
    break;
    case 18: // Game Over
      ChangeGameState( GameOver );
      return;
    break;
  }
  SequenceStage = nextSequence;
}

void DrawCombatScreen( bool DrawCommands )
{
  // Left Side
  arduboy.display.setColor(BLACK);
  arduboy.display.fillRect( 0, 0, 35, 27 ); //Fill rectangle with BLACK?
  arduboy.display.setColor(WHITE);
  arduboy.display.drawRect(0, 0, 35, 27);
  
  Text::DisplayText(CombatMenu_Atk, 2, 7, true);
  Text::ConvertIntToChar( PlayerShip->HP_Weapons );
  Text::DisplayText( buffer, 22, 7, false );
  
  Text::DisplayText(CombatMenu_Shld, 2, 13, true);
  Text::ConvertIntToChar( PlayerShip->HP_Shields );
  Text::DisplayText( buffer, 22, 13, false );
  
  Text::DisplayText(CombatMenu_Hull, 2, 19, true);
  Text::ConvertIntToChar( PlayerShip->HP_Hull );
  Text::DisplayText( buffer, 22, 19, false);

  Text::DisplayText( CombatMenu_Player, 2, 1, true );

  // Right Side
  arduboy.display.setColor(BLACK);
  arduboy.display.fillRect( 52, 0, 32, 27 );
  arduboy.display.setColor(WHITE);
  arduboy.display.drawRect( 52, 0, 32, 27);
  Text::DisplayText( CombatMenu_Enemy, 54, 1, true );
  
  Text::DisplayText(CombatMenu_Atk, 54, 7, true);
  Text::ConvertIntToChar( LatestPlanetEncountered->Attack );
  Text::DisplayText( buffer, 70, 7, false );
  
  Text::DisplayText(CombatMenu_Def, 54, 13, true);
  Text::ConvertIntToChar( LatestPlanetEncountered->Defense );
  Text::DisplayText( buffer, 70, 13, false );

  // Orders
  if ( DrawCommands )
  {
    // Selection Arrow
    if ( DPad == None && AcceptMenuInput == false )
      AcceptMenuInput = true;
  
    if ( DPad == Up && AcceptMenuInput )
    {
      CombatSelectionArrow->SelectionMoveUp();
      AcceptMenuInput = false;
    }
    else if ( DPad == Down && AcceptMenuInput )
    {
      CombatSelectionArrow->SelectionMoveDown();
      AcceptMenuInput = false;
    }
  
    Text::DisplayTextClear( Cmd_Atk, 8, 25, true, false );
    Text::DisplayTextClear( Cmd_Repair, 8, 32, true, false );
    Text::DisplayTextClear( Cmd_Flee, 8, 39, true, false );
  
    CombatSelectionArrow->Draw();
    arduboy.display.drawRect( 0, 25, 84, 23 );
  }
}

void GenerateReward( Loot reward )
{
  int index = 0;
  int upgradeAmount = 0;

  // Display initial text
  if (reward == 0)
  {
//    index = 25;
    index = Text::CopyIntoBuffer( DiscoveredNothing, 0, 25);
  }
  else if (reward > 4)
  {
//    index = 22;
    index = Text::CopyIntoBuffer( DiscoveredGood, 0, 7 );
  }
  else
  {
//    index = 35;
    index = Text::CopyIntoBuffer( DiscoveredUpgrade, 0, 28 );
  }

  upgradeAmount = PlayerShip->Upgrade(reward);
  
  switch (reward)
  {
    case NoLoot:
    
    break;
    case LootHull:
      index += Text::CopyIntoBuffer( THull, index, 4 );
    break;
    case LootWeapons:
      index += Text::CopyIntoBuffer( TWeapons, index, 7 );
    break;
    case LootShields:
      index += Text::CopyIntoBuffer( TShields, index, 7 );
    break;
    case LootEngines:
      index += Text::CopyIntoBuffer( TEngines, index, 7 );
    break;
    case LootCrew:
      index +=Text::CopyIntoBuffer( CapturedCrew, index, 13 );
    break;
    case LootFuel:
      index += Text::CopyIntoBuffer( TFuel, index, 7 );
    break;
  }
  typeBuffer[index] = '\0';
}


//static void DrawStatusBar( int x, int y, int length, int height, float fill )  // To save about 100 bytes
/*static void DrawStatusBar( int x, int y, int length, int height, int fill )
{
  length *= 2;
  int fillTo = x + floor( fill * length / 100.0f );
  
  for ( int i(0); i < height; i++ )
  {
    int xOffset = abs( height - ( ceil( height / 2.0f ) + i ) );
    int startX = x + xOffset;
    int startY = y + i;
    int endX = startX + length - ( 2 * xOffset );
    if ( i == 0 || i == (height - 1) )
      arduboy.display.drawLine( startX, startY, endX, startY );
    else
    {
      arduboy.display.drawPixel( startX, startY );
      arduboy.display.drawPixel( startX + length - ( 2 * xOffset ), startY );
    }

    // Draw Fill
    if ( i != 0 && i != (height - 1) )
    {
      arduboy.display.drawLine( startX, startY, fillTo , startY );
    }
  }
}*/

void ResetPlayer()
{
  Ship::SetupShip( PlayerShip );
  TimeUntilNextRepair = RepairTime;
}

void NextSector()
{
  CurrentSector++;
  
  if ( CurrentSector >= 7 )
  {
    ChangeGameState( WinGame );
    return;
  }
  LatestPlanetEncountered = NULL;
  CanHail = false;
  
//  DeleteMap();
  NewMap();
  PlayerShip->MapPosition->x = 0;
  PlayerShip->MapPosition->y = 0;
  PlayerShip->ShipRotation = 90;
//  GenerateRandomEncounter();
}

void WinGameLoop()
{
  bool done = false;
  
  if ( SequenceStage < 4 )
  {
//    _StarField->Draw();
    arduboy.display.drawBitmap( 68, 0, PlanetHome_16_64 );
    arduboy.display.drawBitmap( 42, 24, PlayerBitMaps[2] );

    ClockUpdate( false );
  }
  
  if ( SequenceStage == 1 )
  {
    done = TextManager->DisplayTextOverTime( GameWin1, 0, 2 ) && BButton;
  }
  else if ( SequenceStage == 2 )
  {
    done = TextManager->DisplayTextOverTime( GameWin2, 0, 2 );
  }
  else if ( SequenceStage == 3 )
  {
    done = TextManager->DisplayTextOverTime( GameWin3, 0, 2 );
  }
  else if ( SequenceStage == 4 )
  {
    done = TextManager->DisplayTextOverTime( GameWin4, 0, 2 );
  }
  if ( done && BButton )
  {
    TextManager->NewDisplayTextOverTime();
    SequenceStage++;
    if ( SequenceStage == 5 )
      ChangeGameState( Reset );
  }
}

void GameOverLoop( int ending )
{
  bool done = false;
  
  if ( ending == 1 )
  {
    if ( SequenceStage == 1 )
    {
      done = TextManager->DisplayTextOverTime( Defeat_A, 0, 32 );
    }
    else if ( SequenceStage == 2 )
    {
      done = TextManager->DisplayTextOverTime( Defeat_B, 0, 32 );
    }
    else if ( SequenceStage == 3 )
    {
      done = TextManager->DisplayTextOverTime( Defeat_C, 0, 32 );
    }
    else if ( SequenceStage == 4 )
      ChangeGameState( Reset );
    
  }
  else if ( ending == 2 )
  {
    if ( SequenceStage == 1 )
    {
      done = TextManager->DisplayTextOverTime( Defeat_D, 0, 20 );
    }
    else if ( SequenceStage == 2 )
    {
      done = TextManager->DisplayTextOverTime( Defeat_E, 0, 20 );
    }
    else if ( SequenceStage == 3 )
      ChangeGameState( Reset );
  }
  if ( done && BButton )
  {
    TextManager->NewDisplayTextOverTime();
    SequenceStage++;
  }
}

void SetupSectorReachedText()
{
  StatusUpdateTime = 240;
  StatusUpdateAvailable = true;
  StatusUpdateFromProgMem = false;
  Text::CopyIntoBuffer( SectorReachedA, 0, 16 );
  Text::ConvertIntToChar( 60 + random( 1, 10 )  - ( CurrentSector * 10 ), typeBuffer, 16 );
  typeBuffer[18] = '\0';
  Status_Update = typeBuffer;
}

void ClockUpdate( bool runnning )
{
  // Slow it down because it was too hard?
  if ( runnning ) seconds -= ( DeltaTime * 1.0f );
  if ( seconds < 0 ) 
  {
    if ( minutes == 0 )
    {
      // Game Over
      ChangeGameState( TimeUp );
    }
    
    minutes -= 1;
    seconds = 59.99;
  }

  Text::ConvertIntToChar( minutes, clockBuffer, 0 );
  clockBuffer[1] =  ':';
  if ( seconds < 10 )
  {
    clockBuffer[2] = '0';
    Text::ConvertIntToChar( seconds, clockBuffer, 3 );
  }
  else
    Text::ConvertIntToChar( seconds, clockBuffer, 2 );
  clockBuffer[4] = '\0';
  Text::DisplayText( clockBuffer, 84-16, 34, false );
}

/*
 * To Do
 * 
 *  
 * 
 *  
/*
 * Notes:
 * 
 * Random encounters
 * Random space debris
 * Not all Planets are encounters
 * 
 *  Note: It would be cool to render wreckage so you can see where you've been
 */
