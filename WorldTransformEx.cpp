#include "WorldTransform.h"
#include"math/Matrix/MatrixTrans.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(
	    scale_, rotation_, translation_
	);
	TransferMatrix();
}