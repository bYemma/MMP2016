#include "Projectile.h"

class NadeProjectile : public Projectile {
public:
	NadeProjectile();

	virtual Projectile* clone()
	{
		return new NadeProjectile();
	}


};