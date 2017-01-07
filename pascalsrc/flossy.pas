program flossy;

uses Crt, math, SDL2, SDL2_image, SDL_ttf;

const
    WIDTH = 640+320;
    HEIGHT = 360+180;
    ROTATION = 2;
    VELOCITY = 4;

type
    TSprite = Record
        t : PSDL_Texture;
        r : PSDL_Rect;
        x : Integer;
        y : Integer;
        velocity : Single;
        angle : Single;
        rotation : Single;
    end;

var
    Player1 : TSprite;
    Player2 : TSprite;
    Sheep : TSprite;
    Window : PSDL_Window;
    Font10 : PTTF_Font;
    Font20 : PTTF_Font;
    Renderer : PSDL_Renderer;
    image : PSDL_Surface;  	
    event : PSDL_Event;
    running : Boolean;
    current, delta : Cardinal;

procedure Intersect;
var
    top,bottom,left,right, paddle1, paddle2 : Boolean;
begin
    left := ((Sheep.r^.x <= Player1.r^.x + Player1.r^.w) 
        and (Sheep.r^.y > Player1.r^.y) 
        and (Sheep.r^.y + Sheep.r^.h < Player1.r^.y + Player1.r^.h));
    right := ((Sheep.r^.x >= Player2.r^.x)
        and (Sheep.r^.y > Player2.r^.y)
        and (Sheep.r^.y + Sheep.r^.h < Player2.r^.y + Player2.r^.h));
    if Sheep.r^.y <= 0 then top := true;
    if Sheep.r^.y >= HEIGHT - Sheep.r^.h then bottom := true;

    if top or bottom then begin
        Sheep.angle := Sheep.angle + 90;
        Sheep.angle := round(Sheep.angle) mod round(360.0);
    end;

    if left then begin 
        writeln('Hit Paddle 1!');
        Sheep.angle := Sheep.angle + 90;
        Sheep.angle := round(Sheep.angle) mod round(360);
    end;
    if right then begin
        writeln('Hit Paddle 2!');
        Sheep.angle := Sheep.angle + 90;
        Sheep.angle := round(Sheep.angle) mod round(360);
    end;

end;


procedure UpdateSheep;
var
	dx, dy : Single;
    rad : Single;
begin
    if Sheep.rotation > 360 then Sheep.rotation := 0;
    Sheep.rotation := Sheep.rotation + ROTATION;
    rad := DegToRad(Sheep.angle);
    dx := Sheep.velocity * cos(rad);
    dy := Sheep.velocity * sin(rad);
    Sheep.x := round(dx);
    Sheep.y := round(dy);

    Sheep.r^.x := Sheep.r^.x + Sheep.x;
    Sheep.r^.y := Sheep.r^.y + Sheep.y;
    Intersect;
	
end;

begin
	ClrScr;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    Window := SDL_CreateWindow('SheePong', 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    Renderer := SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    image := IMG_Load('assets/image/sheep.png');
    new(Sheep.r);
    Sheep.r^.w := image^.w;
    Sheep.r^.h := image^.h;
    Sheep.t := SDL_CreateTextureFromSurface(Renderer, image);
    Sheep.r^.x := round(WIDTH/2 - Sheep.r^.w/2);
    sheep.r^.y := round(HEIGHT/2 - Sheep.r^.h/2);
    Sheep.velocity := 2;
    Sheep.angle := 120;
	SDL_FreeSurface(image);

    image := IMG_Load('assets/image/paddler.png');
    new(Player1.r);
    Player1.r^.w := image^.w;
    Player1.r^.h := image^.h;
    Player1.t := SDL_CreateTextureFromSurface(Renderer, image);
    Player1.r^.x := 0;
    Player1.r^.y := round(HEIGHT/2 - Player1.r^.h/2);
    SDL_FreeSurface(image);

    image := IMG_Load('assets/image/paddlel.png');
    new(Player2.r);
    Player2.r^.w := image^.w;
    Player2.r^.h := image^.h;
    Player2.t := SDL_CreateTextureFromSurface(Renderer, image);
    Player2.r^.x := WIDTH - Player2.r^.w;
    Player2.r^.y := round(HEIGHT/2 - Player2.r^.h/2);
    SDL_FreeSurface(image);


    Font10 := TTF_OpenFont('flubber.ttf', 10);
    Font20 := TTF_OpenFont('flubber.ttf', 20);

    running := true;
	new(event);

    current := SDL_GetTicks;
    delta := current;
    while running do begin
    	if (SDL_PollEvent(event) > 0) then begin
        	if event^.type_ = SDL_QUITEV then running := false;

            if event^.type_ = SDL_MOUSEMOTION then begin
            	Player1.r^.y := event^.motion.y;
                if Player1.r^.y > (HEIGHT - Player1.r^.h) then Player1.r^.y := HEIGHT-Player1.r^.h;
                // TODO: Make some AI
                Player2.r^.y := Player1.r^.y;
            end;

            if event^.type_ = SDL_KEYDOWN then begin
            	if event^.key.keysym.sym = SDLK_ESCAPE then running := false;
            end;
        end;


        UpdateSheep;
		//TODO; Fix rotation according to physics

        		

        (* Call update for all three sprites *)
        SDL_RenderClear(Renderer);
        SDL_RenderCopyEx(Renderer, Sheep.t, nil, Sheep.r, Sheep.rotation, nil, SDL_FLIP_NONE);
		//SDL_RenderCopy(Renderer, Sheep.t, nil, Sheep.r);
        SDL_RenderCopy(Renderer, Player1.t, nil, Player1.r);
        SDL_RenderCopy(Renderer, Player2.t, nil, Player2.r);
        SDL_RenderPresent(Renderer);
        delta := SDL_GetTicks - current;
        current := SDL_GetTicks;
        if (32 - delta) > 10 then SDL_Delay(32 - delta);
    end;
    SDL_Quit;
end.


