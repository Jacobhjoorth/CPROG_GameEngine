 - Beskrivning - 
Jag gjorde två olika spel för att kunna testa att spelmotorn fungerade för olika typer av spel. Spelet Starship är det spelet som jag är mest nöjd med, och som du som testare borde köra först. 

 - Starship - 
I Starship ska du som spelare skjuta ner, alternativt fånga fiender med din “Pistol”. Fienderna kommer flygandes uppifrån och som rör sig mot dig i y-led. Ditt mål är att skjuta ner/fånga 20 st fiender. Om 3 st fiender lyckas ta sig förbi dig så förlorar du. Du kontrollerar din pistol med musen, och skjuter genom att klicka på musen.

 - RabbitHammer - 
I RabbitHammer ska du som spelare hamra med “Sledgehammer” på fiender som dyker upp på skärmen. Fienderna kan dyka upp på olika platser på skärmen. Målet är att hamra 20 st fiender. Om du inte hamrar fienderna under en viss tid så kommer de försvinna. Om 3 st fiender försvinner innan du hamrat dem så kommer du förlora. Du kontrollerar din sledgehammer med musen, och hamrar genom att klicka på musen.


- Instruktion för att bygga och testa - 

 - Sökvägar - 
Resursfilerna ligger i resources-mappen i projektet och alla sprites använder sig av en “constants.h”-fil för att hitta mappen. I resources-mappen så finns det tre mappar(fonts, images, sounds).
 - Ex (för att hitta filer i images-mappen):
shipTexture = IMG_LoadTexture(sys.ren, (constants::gResPath + "images/Enemy.png").c_str());

 - Starship - 
I första steget för att bygga och testa spelet Starship ska du i Main,  initiera en Pistol, en EnemySpawner och en HealthHandler genom getInstance(). Och sedan lägga till dessa Sprites genom funktionen addSprite() som ligger i GameEngine. Du ska sedan kalla på run(), som också ligger i GameEngine. 

Andra steget är att du går in i EnemySpawner och lägger till randomSpawnShip() i funktionen tick().

Sista steget är att gå in i HealthHandler och sätta currentHealth, totalHealth, enemiesToKillTxt och enemiesToKill. Detta sätter hälsan på spelaren, hur många fiender man behöver döda samt en sträng för fiendens liv. Strängen för spelarens liv behöver man inte ändra på eftersom det alltid ska stå “Health”.

 - Main - 
int main(int argc, char **argv)
{
      Pistol *pistol = Pistol::getInstance();
   EnemySpawner* spawner = EnemySpawner::getInstance();
   HealthHandler *handler = HealthHandler::getInstance();

   ge.addSprite(pistol);
   ge.addSprite(spawner);
   ge.addSprite(handler);
   ge.run();

   return 0;
}

 - EnemySpawner - 
void EnemySpawner::EnemySpawner::tick()
{
   randomSpawnShip();
}

 - HealthHandler - 
HealthHandler::HealthHandler() : Sprite(100, 100, 100, 100){
   // Set total health
   ge.setTotalHealth(3);

   // Set current health
   ge.setCurrentHealth(3);
   // Set enemies to kill string
   ge.setEnemiesToKillTxt(“Ships to destroy: “);
   // Set enemies to kill
   ge.setEnemiesToKill(20);
}

 - RabbitHammer - 
I första steget för att bygga och testa spelet RabbitHammer ska du i Main,  initiera en Sledgehammer och en EnemySpawner genom getInstance(). Och sedan lägga till dessa Sprites genom funktionen addSprite() som ligger i GameEngine. Du ska sedan kalla på run(), som också ligger i GameEngine. 

Andra steget är att du går in i EnemySpawner och lägger till randomSpawnRabbit() i funktionen tick().

Sista steget är att gå in i HealthHandler och sätta currentHealth, totalHealth, enemiesToKillTxt och enemiesToKill. Detta sätter hälsan på spelaren, hur många fiender man behöver döda samt en sträng för fiendens liv. Strängen för spelarens liv behöver man inte ändra då eftersom det alltid ska stå “Health”.

 - Main - 
int main(int argc, char **argv)
{      
   Sledgehammer* sledgehammer = Sledgehammer::getInstance();
   EnemySpawner* spawner = EnemySpawner::getInstance();
   HealthHandler *handler = HealthHandler::getInstance();
   ge.addSprite(sledgehammer);
   ge.addSprite(spawner);
   ge.addSprite(handler);
   ge.run();

   return 0;
}

 - EnemySpawner - 
void EnemySpawner::EnemySpawner::tick()
{
   randomSpawnRabbit();
}

 - HealthHandler - 
HealthHandler::HealthHandler() : Sprite(100, 100, 100, 100){
   // Set total health
   ge.setTotalHealth(3);

   // Set current health
   ge.setCurrentHealth(3);
   // Set enemies to kill string
   ge.setEnemiesToKillTxt(“Rabbits to hit: “);
   // Set enemies to kill
   ge.setEnemiesToKill(20);
}