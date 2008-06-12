#include "plPointChannel.h"

// plPointChannel //
plPointChannel::plPointChannel() { }
plPointChannel::~plPointChannel() { }

IMPLEMENT_CREATABLE(plPointChannel, kPointChannel, plAGChannel)


// plPointBlend //
plPointBlend::plPointBlend() { }
plPointBlend::~plPointBlend() { }

IMPLEMENT_CREATABLE(plPointBlend, kPointBlend, plPointChannel)


// plPointConstant //
plPointConstant::plPointConstant() { }
plPointConstant::~plPointConstant() { }

IMPLEMENT_CREATABLE(plPointConstant, kPointConstant, plPointChannel)

void plPointConstant::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fResult.read(S);
}

void plPointConstant::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    fResult.write(S);
}

void plPointConstant::IPrcWrite(pfPrcHelper* prc) {
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Result");
    fResult.prcWrite(prc);
    prc->closeTag();
}

void plPointConstant::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Result") {
        if (tag->hasChildren())
            fResult.prcParse(tag->getFirstChild());
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}


// plPointControllerCacheChannel //
plPointControllerCacheChannel::plPointControllerCacheChannel() { }
plPointControllerCacheChannel::~plPointControllerCacheChannel() { }

IMPLEMENT_CREATABLE(plPointControllerCacheChannel,
                    kPointControllerCacheChannel,
                    plPointChannel)


// plPointControllerChannel //
plPointControllerChannel::plPointControllerChannel() : fController(NULL) { }

plPointControllerChannel::~plPointControllerChannel() {
    if (fController != NULL)
        delete fController;
}

IMPLEMENT_CREATABLE(plPointControllerChannel, kPointControllerChannel,
                    plPointChannel)

void plPointControllerChannel::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fController = plController::Convert(mgr->ReadCreatable(S));
}

void plPointControllerChannel::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    mgr->WriteCreatable(S, fController);
}

void plPointControllerChannel::IPrcWrite(pfPrcHelper* prc) {
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Controller");
    fController->prcWrite(prc);
    prc->closeTag();
}

void plPointControllerChannel::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Controller") {
        if (tag->hasChildren())
            fController = plController::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}


// plPointTimeScale //
plPointTimeScale::plPointTimeScale() { }
plPointTimeScale::~plPointTimeScale() { }

IMPLEMENT_CREATABLE(plPointTimeScale, kPointTimeScale, plPointChannel)


// plPointChannelApplicator //
plPointChannelApplicator::plPointChannelApplicator() { }
plPointChannelApplicator::~plPointChannelApplicator() { }

IMPLEMENT_CREATABLE(plPointChannelApplicator, kPointChannelApplicator,
                    plAGApplicator)