#include"EnemyApproach.h"


void EnemyStateApproach::Update(Enemy* enemy) {

	enemy->SetVelocity({0.0f, 0.0f, -0.2f});

	enemy->SetTranslation(Add(enemy->GetTranslation(), enemy->GetVelocity()));

	// 規定の位置に到達したら離脱
	if (enemy->GetTranslation().z < 0.0f) {
		enemy->ChangeState(new EnemyStateLeave());
	}
}
