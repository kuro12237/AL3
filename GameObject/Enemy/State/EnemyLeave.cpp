#include"EnemyLeave.h"


void EnemyStateLeave::Update(Enemy* enemy)
{ enemy->SetVelocity({0.3f, 0.3f, -0.2f}); }
