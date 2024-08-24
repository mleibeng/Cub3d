### Cub3d

Raycasting project for creating an old-school Doom lookalike.

Bonuses include Adding Doors, Wall collision, minimap, animations and mouse control.

---

This project is meant to introduce more advanced 3d features, specifically raycasting.

---

### How Ray-Casting works:

![Cameras_local_coordinate_system](https://github.com/user-attachments/assets/df0e27a4-3f45-4c22-a803-feb5489ef9d4)

Explanation:

For each pixel in out window, we send out a ray that sends us feedback on the distance between us, the player and the first object hit, in the case of this project the walls/doors.
Depending on the distance measured between us and the object we adjust the angle and size in which we display this object, creating a 3 dimensional effect, projecting further objects as smaller than closer ones.

Too create an accurate measurement the distance and movement to an object is measured in floats, even though the map is only gridded in integers. 
This improves the performance while maintaining accurate distances and making the movement of our player smooth.

Below is an example of movement through our map:

<!-- <div> insert video of our program here </div> -->
