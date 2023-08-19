#include "WorldTransform.h"
#include"math/MatrixTransform.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ =MatrixTransform::MakeAffineMatrix(scale_, rotation_, translation_);
	TransferMatrix();
}