#include "WorldTransform.h"
#include"MatrixTrans.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(
	    scale_, rotation_, translation_
	);
	TransferMatrix();


}