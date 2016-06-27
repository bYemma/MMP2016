
class GameState 
{
public:
	//pressed = man hält die taste gedrückt, released = man lässt eine taste los

	//Move
	virtual void handle_A_Pressed() = 0;
	virtual void handle_D_Pressed() = 0;
	
	//Jump
	virtual void handle_SHIFT_Pressed() = 0;
	
	//Aim
	virtual void handle_UP_Pressed() = 0;
	virtual void handle_DOWN_Pressed() = 0;
	virtual void handle_LEFT_Pressed() = 0;
	virtual void handle_RIGHT_Pressed() = 0;

	//Load shot and fire
	virtual void handle_SPACE_Pressed() = 0;
	virtual void handle_SPACE_Released() = 0;

	//Beende Spiel
	virtual void handle_ESC_Released() = 0;

	//Auswahl der Waffen
	virtual void handle_1_Released() = 0;
	virtual void handle_2_Released() = 0;
	virtual void handle_3_Released() = 0;

protected:
	GameState();
	virtual ~GameState();

};



