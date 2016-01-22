==================
2D Shmup Prototype !
==================

This is a basic prototype for a 2D shmup idea I had one day.

The idea was to combine shmups and roguelikes by having a game
where the waves of enemies was randomly determined each time you
played.

Each ship follows a randomly determined path. There is a small
chance each frame that the ship will abandon its path and instead
seek to collide with the player.

The AI uses a state machine to encapsulate this behaviour.








// Compilation ///////////////////////////////////////

This was compiled with Visual C++ 9.0 Express Edition.

You will also need to have the Dark GDK installed in order
to compile. This is a free API for game development.
See:
http://www.thegamecreators.com/?m=view_product&id=2128

