#include "Branch.h"


Branch::Branch()
{
	Position = Point(0, 0, 0);
	NumElements = 0;
}

Branch::Branch(Point position, float width)
{
	NumElements = 0;
	Position = position;
	Width = width;

}

void Branch::Init(Point position, float width)
{
	Position = position;
	Width = width;
}

void Branch::Add(Entity entity) {
	if (NumElements < MAXIMUMCOLLISIONELEMENTS) {
		Entities.push_back(entity);
		NumElements++;
		return;
	}
	else {
		NumElements = 0;
		isSplit = true;
		Branches = new Branch[8];
		/* Layer

		P________
		|_A_|_B_|
		|_C_|_D_|

		*/

		//Layer 1
		//A
		Branches[0].Init(Position, Width / 2);
		//B
		Branches[1].Init(Point(Position.X + Width / 2, Position.Y, Position.Z), Width / 2);
		//C
		Branches[2].Init(Point(Position.X, Position.Y + Width / 2, Position.Z), Width / 2);
		//D
		Branches[3].Init(Point(Position.X + Width / 2, Position.Y + Width / 2, Position.Z), Width / 2);

		//Layer 2
		//A
		Branches[4].Init(Point(Position.X, Position.Y, Position.Z + Width / 2), Width / 2);
		//B
		Branches[5].Init(Point(Position.X + Width / 2, Position.Y, Position.Z + Width / 2), Width / 2);
		//C
		Branches[6].Init(Point(Position.X, Position.Y + Width / 2, Position.Z + Width / 2), Width / 2);
		//D
		Branches[7].Init(Point(Position.X + Width / 2, Position.Y + Width / 2, Position.Z + Width / 2), Width / 2);

		for (Entity en : Entities) {
			if (en.GetWidth() > Width / 2 || en.GetLength() > Width / 2 || en.GetHeight() > Width / 2)
				continue;

			//this assumes 0, 0, 0 is the bottom left of the world space (NO NEGATIVE VALUES)
			//TODO modify for a 0, 0, 0 center with changing cells
			//TODO check if the height width or length exceeds the bounds of the branch
			if (en.GetPosition().X > Position.X + Width / 2) {
				if (en.GetPosition().Z > Position.Z + Width / 2) {
					if (en.GetPosition().Y > Position.Y + Width / 2) {
						//if(en.GetPosition().X + en.GetWidth || )
						Branches[7].Add(en);
						continue;
					}
					else {
						Branches[5].Add(en);
						continue;
					}

				}
				else {
					if (en.GetPosition().Y > Position.Y + Width / 2) {
						Branches[3].Add(en);
						continue;
					}
					else {
						Branches[1].Add(en);
						continue;
					}

				}
			}
			else {
				if (en.GetPosition().Z > Position.Z + Width / 2) {
					if (en.GetPosition().Y > Position.Y + Width / 2) {
						Branches[6].Add(en);
						continue;
					}
					else {
						Branches[4].Add(en);
						continue;
					}
				}
				else {
					if (en.GetPosition().Y > Position.Y + Width / 2) {
						Branches[2].Add(en);
						continue;
					}
					else {
						Branches[0].Add(en);
						continue;
					}
				}
			}
		}
	}
}

void Branch::Remove(Entity entity) {

}

void Branch::GetCollidableEntities(float x, float y, float z, int collisionIDs[]) {
	//TODO
	//check against entities in this Branch
	if (isSplit) {
		//send off to a sub Branch
	}
}

void Branch::EntityMoved() {
	//TODO: this Function

	//check for leaving current branch, pass up a branch
	//possibly call function recalculate
}


Branch::~Branch()
{
}
