#include "WorldTransform.h"
#include"Matrix/MatrixTrans.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(
	    scale_, rotation_, translation_
	);
	TransferMatrix();


}