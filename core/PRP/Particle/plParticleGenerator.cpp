/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plParticleGenerator.h"

/* plOneTimeParticleGenerator */
plOneTimeParticleGenerator::~plOneTimeParticleGenerator() {
    delete[] fPosition;
    delete[] fDirection;
}

void plOneTimeParticleGenerator::read(hsStream* S, plResManager* mgr) {
    fCount = S->readInt();
    fXSize = S->readFloat();
    fYSize = S->readFloat();
    fScaleMin = S->readFloat();
    fScaleMax = S->readFloat();
    fPartRadsPerSecRange = S->readFloat();

    clearParticles();
    if (fCount > 0) {
        fPosition = new hsVector3[fCount];
        fDirection = new hsVector3[fCount];
        for (size_t i=0; i<fCount; i++) {
            fPosition[i].read(S);
            fDirection[i].read(S);
        }
    }
}

void plOneTimeParticleGenerator::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fCount);
    S->writeFloat(fXSize);
    S->writeFloat(fYSize);
    S->writeFloat(fScaleMin);
    S->writeFloat(fScaleMax);
    S->writeFloat(fPartRadsPerSecRange);

    for (size_t i=0; i<fCount; i++) {
        fPosition[i].write(S);
        fDirection[i].write(S);
    }
}

void plOneTimeParticleGenerator::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("GeneratorParams");
    prc->writeParam("XSize", fXSize);
    prc->writeParam("YSize", fYSize);
    prc->writeParam("ScaleMin", fScaleMin);
    prc->writeParam("ScaleMax", fScaleMax);
    prc->writeParam("RadsPerSecond", fPartRadsPerSecRange);
    prc->endTag(true);

    prc->writeSimpleTag("ParticleSources");
    for (size_t i=0; i<fCount; i++) {
        prc->writeSimpleTag("Source");
        prc->writeSimpleTag("Position");
        fPosition[i].prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("Direction");
        fDirection[i].prcWrite(prc);
        prc->closeTag();
        prc->closeTag();  // Source
    }
    prc->closeTag();
}

void plOneTimeParticleGenerator::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "GeneratorParams") {
        fXSize = tag->getParam("XSize", "0").to_float();
        fYSize = tag->getParam("YSize", "0").to_float();
        fScaleMin = tag->getParam("ScaleMin", "0").to_float();
        fScaleMax = tag->getParam("ScaleMax", "0").to_float();
        fPartRadsPerSecRange = tag->getParam("RadsPerSecond", "0").to_float();
    } else if (tag->getName() == "ParticleSources") {
        fCount = tag->countChildren();
        clearParticles();
        if (fCount > 0) {
            fPosition = new hsVector3[fCount];
            fDirection = new hsVector3[fCount];
            const pfPrcTag* child = tag->getFirstChild();
            for (size_t i=0; i<fCount; i++) {
                if (child->getName() != "Source")
                    throw pfPrcTagException(__FILE__, __LINE__, child->getName());
                const pfPrcTag* subChild = child->getFirstChild();
                while (subChild != NULL) {
                    if (subChild->getName() == "Position") {
                        if (subChild->hasChildren())
                            fPosition[i].prcParse(subChild->getFirstChild());
                    } else if (subChild->getName() == "Direction") {
                        if (subChild->hasChildren())
                            fDirection[i].prcParse(subChild->getFirstChild());
                    } else {
                        throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                    }
                    subChild = subChild->getNextSibling();
                }
                child = child->getNextSibling();
            }
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plOneTimeParticleGenerator::clearParticles() {
    delete[] fPosition;
    delete[] fDirection;
    fPosition = NULL;
    fDirection = NULL;
}


/* plSimpleParticleGenerator */
plSimpleParticleGenerator::~plSimpleParticleGenerator() {
    delete[] fInitPos;
    delete[] fInitPitch;
    delete[] fInitYaw;
}

void plSimpleParticleGenerator::read(hsStream* S, plResManager* mgr) {
    fGenLife = S->readFloat();
    fPartLifeMin = S->readFloat();
    fPartLifeMax = S->readFloat();
    fParticlesPerSecond = S->readFloat();

    fNumSources = S->readInt();
    clearSources();
    if (fNumSources > 0) {
        fInitPos = new hsVector3[fNumSources];
        fInitPitch = new float[fNumSources];
        fInitYaw = new float[fNumSources];
        for (size_t i=0; i<fNumSources; i++) {
            fInitPos[i].read(S);
            fInitPitch[i] = S->readFloat();
            fInitYaw[i] = S->readFloat();
        }
    }

    fAngleRange = S->readFloat();
    fVelMin = S->readFloat();
    fVelMax = S->readFloat();
    fXSize = S->readFloat();
    fYSize = S->readFloat();
    fScaleMin = S->readFloat();
    fScaleMax = S->readFloat();
    fPartMassRange = S->readFloat();
    fPartRadsPerSecRange = S->readFloat();
}

void plSimpleParticleGenerator::write(hsStream* S, plResManager* mgr) {
    S->writeFloat(fGenLife);
    S->writeFloat(fPartLifeMin);
    S->writeFloat(fPartLifeMax);
    S->writeFloat(fParticlesPerSecond);

    S->writeInt(fNumSources);
    for (size_t i=0; i<fNumSources; i++) {
        fInitPos[i].write(S);
        S->writeFloat(fInitPitch[i]);
        S->writeFloat(fInitYaw[i]);
    }

    S->writeFloat(fAngleRange);
    S->writeFloat(fVelMin);
    S->writeFloat(fVelMax);
    S->writeFloat(fXSize);
    S->writeFloat(fYSize);
    S->writeFloat(fScaleMin);
    S->writeFloat(fScaleMax);
    S->writeFloat(fPartMassRange);
    S->writeFloat(fPartRadsPerSecRange);
}

void plSimpleParticleGenerator::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("ParticleParams");
    prc->writeParam("GenLife", fGenLife);
    prc->writeParam("PartLifeMin", fPartLifeMin);
    prc->writeParam("PartLifeMax", fPartLifeMax);
    prc->writeParam("ParticlesPerSecond", fParticlesPerSecond);
    prc->writeParam("ParticleMass", fPartMassRange);
    prc->writeParam("RadsPerSecond", fPartRadsPerSecRange);
    prc->endTag(true);

    prc->startTag("GeneratorParams");
    prc->writeParam("AngleRange", fAngleRange);
    prc->writeParam("VelMin", fVelMin);
    prc->writeParam("VelMax", fVelMax);
    prc->writeParam("XSize", fXSize);
    prc->writeParam("YSize", fYSize);
    prc->writeParam("ScaleMin", fScaleMin);
    prc->writeParam("ScaleMax", fScaleMax);
    prc->endTag(true);

    prc->writeSimpleTag("ParticleSources");
    for (size_t i=0; i<fNumSources; i++) {
        prc->startTag("Source");
        prc->writeParam("Pitch", fInitPitch[i]);
        prc->writeParam("Yaw", fInitYaw[i]);
        prc->endTag();
        fInitPos[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}

void plSimpleParticleGenerator::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ParticleParams") {
        fGenLife = tag->getParam("GenLife", "0").to_float();
        fPartLifeMin = tag->getParam("PartLifeMin", "0").to_float();
        fPartLifeMax = tag->getParam("PartLifeMax", "0").to_float();
        fParticlesPerSecond = tag->getParam("ParticlesPerSecond", "0").to_float();
        fPartMassRange = tag->getParam("ParticleMass", "0").to_float();
        fPartRadsPerSecRange = tag->getParam("RadsPerSecond", "0").to_float();
    } else if (tag->getName() == "GeneratorParams") {
        fAngleRange = tag->getParam("AngleRange", "0").to_float();
        fVelMin = tag->getParam("VelMin", "0").to_float();
        fVelMax = tag->getParam("VelMax", "0").to_float();
        fXSize = tag->getParam("XSize", "0").to_float();
        fYSize = tag->getParam("YSize", "0").to_float();
        fScaleMin = tag->getParam("ScaleMin", "0").to_float();
        fScaleMax = tag->getParam("ScaleMax", "0").to_float();
    } else if (tag->getName() == "ParticleSources") {
        fNumSources = tag->countChildren();
        clearSources();
        if (fNumSources > 0) {
            fInitPos = new hsVector3[fNumSources];
            fInitPitch = new float[fNumSources];
            fInitYaw = new float[fNumSources];
            const pfPrcTag* child = tag->getFirstChild();
            for (size_t i=0; i<fNumSources; i++) {
                if (child->getName() != "Source")
                    throw pfPrcTagException(__FILE__, __LINE__, child->getName());
                fInitPitch[i] = tag->getParam("Pitch", "0").to_float();
                fInitYaw[i] = tag->getParam("Yaw", "0").to_float();
                if (child->hasChildren())
                    fInitPos[i].prcParse(child->getFirstChild());
                child = child->getNextSibling();
            }
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plSimpleParticleGenerator::clearSources() {
    delete[] fInitPos;
    delete[] fInitPitch;
    delete[] fInitYaw;
    fInitPos = NULL;
    fInitPitch = NULL;
    fInitYaw = NULL;
}
