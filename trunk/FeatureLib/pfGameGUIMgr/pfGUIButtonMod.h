#ifndef _PFGUIBUTTONMOD_H
#define _PFGUIBUTTONMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUIButtonMod : public pfGUIControlMod {
public:
    enum SoundEvents { kMouseDown, kMouseUp, kMouseOver, kMouseOff };
    enum NotifyType { kNotifyOnUp, kNotifyOnDown, kNotifyOnUpAndDown };

protected:
    hsTArray<plKey> fAnimationKeys, fMouseOverAnimKeys;
    plString fAnimName, fMouseOverAnimName;
    bool fClicking, fTriggering;
    hsPoint3 fOrigMouseDownPt;
    plKey fDraggable;
    pfGUICtrlProcObject* fOrigHandler;
    bool fOrigReportedDrag;
    int fNotifyType, fEoaUnknown1, fEoaUnknown2;

public:
    pfGUIButtonMod();
    virtual ~pfGUIButtonMod();

    DECLARE_CREATABLE(pfGUIButtonMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif