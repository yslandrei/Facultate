#include "offersList.h"
#pragma once

int addOffer(offersList* o, offer newOffer);

int popOffer(offersList* o, offer oldOffer);

int modOffer(offersList* o, offer oldOffer, offer newOffer);

offersList createOList();