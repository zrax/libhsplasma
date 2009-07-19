#ifndef _PFGUICONTROLMOD_H
#define _PFGUICONTROLMOD_H

#include "PRP/Modifier/plModifier.h"
#include "Sys/hsColor.h"
#include "Math/hsGeometry3.h"
#include "PRP/Region/hsBounds.h"
#include "Math/hsMatrix44.h"
#include "pfGUIControlHandlers.h"

DllClass pfGUIColorScheme {
public:
    enum FontFlags {
        kFontBold = 0x01,
        kFontItalic = 0x02,
        kFontShadowed = 0x04
    };

private:
    hsColorRGBA fForeColor, fBackColor, fSelForeColor, fSelBackColor;
    int fTransparent;
    plString fFontFace;
    unsigned char fFontSize, fFontFlags;

public:
    pfGUIColorScheme();
    ~pfGUIColorScheme();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

private:
    void IReset();

public:
    hsColorRGBA getForeColor() const;
    hsColorRGBA getBackColor() const;
    hsColorRGBA getSelForeColor() const;
    hsColorRGBA getSelBackColor() const;
    int getTransparent() const;
    plString getFontFace() const;
    unsigned char getFontSize() const;
    unsigned char getFontFlags() const;

    void setForeColor(const hsColorRGBA& color);
    void setBackColor(const hsColorRGBA& color);
    void setSelForeColor(const hsColorRGBA& color);
    void setSelBackColor(const hsColorRGBA& color);
    void setTransparent(int trans);
    void setFontFace(const plString& face);
    void setFontSize(unsigned char size);
    void setFontFlags(unsigned char flags);
};

DllClass pfGUIControlMod : public plSingleModifier {
public:
    enum {
        kWantsInterest, kInheritProcFromDlg, kIntangible, kXparentBgnd,
        kScaleTextWithResolution, kTakesSpecialKeys, kHasProxy,
        kBetterHitTesting, kDerivedFlagsStart = 0x20
    };

protected:
    unsigned int fTagID;
    bool fVisible;
    pfGUICtrlProcWriteableObject* fHandler;
    plKey fDynTextMap, fDynTextLayer;
    pfGUIColorScheme* fColorScheme;
    hsTArray<int> fSoundIndices;
    plKey fProxy, fSkin;

public:
    pfGUIControlMod();
    virtual ~pfGUIControlMod();

    DECLARE_CREATABLE(pfGUIControlMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumSoundIndices() const;
    int getSoundIndex(size_t idx) const;
    void addSoundIndex(int index);
    void setSoundIndices(const hsTArray<int>& indices);
    void clearSoundIndices();

    unsigned int getTagID() const;
    bool getVisible() const;
    pfGUICtrlProcWriteableObject* getHandler() const;
    plKey getDynTextMap() const;
    plKey getDynTextLayer() const;
    pfGUIColorScheme* getColorScheme() const;
    plKey getProxy() const;
    plKey getSkin() const;

    void setTagID(unsigned int id);
    void setVisible(bool visible);
    void setHandler(pfGUICtrlProcWriteableObject* handler);
    void setDynTextMap(plKey map);
    void setDynTextLayer(plKey layer);
    void setColorScheme(pfGUIColorScheme* scheme);
    void setProxy(plKey proxy);
    void setSkin(plKey skin);
};

#endif
