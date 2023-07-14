#include"scene/Enemy/Pattern/EnemyApproach.h"
#include"scene/Enemy/Pattern/EnemyStateLeave.h"


// 接近
void EnemyStateApproach::Update(Enemy* enemy) {

	enemy->SetVelocity({0.0f, 0.0f, -0.2f});

	enemy->SetTranslation(Add(enemy->GetTranslation(), enemy->GetVelocity()));

	// 規定の位置に到達したら離脱
	if (enemy->GetTranslation().z < 0.0f) {
		//enemy->ChangeState(new EnemyStateLeave());
	}
}
