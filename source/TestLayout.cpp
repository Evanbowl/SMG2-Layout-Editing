#include "custom/Actor/TestLayout.h"
#include "Util.h"
#include "Player/MarioAccess.h"
#include "Player/MarioActor.h"

TestLayout::TestLayout() : LayoutActor("TestLayout", 0) {
}

void TestLayout::init(const JMapInfoIter &rIter) {
	MR::connectToSceneLayout(this);
	initLayoutManager("TestLayout", 1);
	appear();
}

static s32 page = 0;

void TestLayout::movement() {

	if (MR::testCorePadTrigger1(0))
		page += 1;
	else if (MR::testCorePadTrigger2(0))
		page -= 1;

	if (page == 3)
		page = 0;
	else if (page == -1)
		page = 2;

	if (page == 2)
		mLayoutActorFlag.mIsHidden = true;
	else
		mLayoutActorFlag.mIsHidden = false;

	TVec2f pointPosP1 = TVec2f(0.0f, 0.0f);
	TVec2f pointPosP2 = TVec2f(0.0f, 0.0f);
	MR::getCorePadPointingPos(&pointPosP1, 0);
	MR::getCorePadPointingPos(&pointPosP2, 1);

    MarioActor* player = MarioAccess::getPlayerActor();

if (page == 0) {//Page 1
	MR::setTextBoxFormatRecursive(this, "TxtText", L"Page 1\nPlayer\nPosition: %.03f, %.03f, %.03f\nRotation: %.03f, %.03f, %.03f\nGravity: %.03f, %.03f, %.03f\nVelocity: %.03f, %.03f, %.03f\nCurrent Animation: %s (%.0f/%.0f)",
	player->mTranslation.x,
	player->mTranslation.y,
	player->mTranslation.z,
	player->mRotation.x,
	player->mRotation.y,
	player->mRotation.z,
	player->getGravityVec()->x,
	player->getGravityVec()->y,
	player->getGravityVec()->z,
	player->mVelocity.x,
	player->mVelocity.y,
	player->mVelocity.z,
	MR::getPlayingBckName(player),
	MR::getBckFrame(player),
	MR::getBckFrameMax(player)
	);
}
else if (page == 1) {//Page 2
	MR::setTextBoxFormatRecursive(this, "TxtText", L"Page 2\nP1 Inputs\nStick X: %.03f, Stick Y: %.03f\nA: %d, B: %d, Z: %d, C: %d\nShake: %d, \nPointer: %.03f, %.03f\nP2 Inputs\nStick X: %.03f, Stick Y: %.03f\nA: %d, B: %d, Z: %d, C: %d\nShake: %d, \nPointer: %.03f, %.03f\n",
	MR::getSubPadStickX(0),
	MR::getSubPadStickY(0),
	MR::testCorePadButtonA(0),
	MR::testCorePadButtonB(0),
	MR::testSubPadButtonZ(0),
	MR::testSubPadButtonC(0),
	MR::isPadSwing(0),
	pointPosP1.x,
	pointPosP1.y,
	MR::getSubPadStickX(1),
	MR::getSubPadStickY(1),
	MR::testCorePadButtonA(1),
	MR::testCorePadButtonB(1),
	MR::testSubPadButtonZ(1),
	MR::testSubPadButtonC(1),
	MR::isPadSwing(1),
	pointPosP2.x,
	pointPosP2.y
	);
}

else if (page == 2) {//Page 3, unused for now.
	MR::setTextBoxFormatRecursive(this, "TxtText", L"Page 3\nStage/Misc\nCurrent Stage: %s %d\n",
	MR::getCurrentStageName(),
	MR::getCurrentScenarioNo()
	);
}
}

void initTestLayout(NameObj* pLayout) {//This function keeps the layout initialized whenever possible.
	MR::connectToSceneLayout(pLayout);

	TestLayout* layout = new TestLayout();
	layout->initWithoutIter();
}
kmCall(0x804657A0, initTestLayout);
