#pragma once
#include <memory>
#include "offer.h"
#include "offersRepository.h"

class undoAction {
public:
	virtual void doUndo() = 0;

	virtual ~undoAction() = default;
};

class undoAdd : public undoAction {
private:
	offer newOffer;
	offersRepository& oRepo;

public:
	undoAdd(const offer& newOffer, offersRepository& oRepo) :
		newOffer{ newOffer },
		oRepo{ oRepo }
	{}

	void doUndo() override {
		oRepo.popOffer(newOffer.getId());
	}
};

class undoPop : public undoAction {
private:
	offer oldOffer;
	offersRepository& oRepo;

public:
	undoPop(const offer& oldOffer, offersRepository& oRepo) :
		oldOffer{ oldOffer },
		oRepo{ oRepo }
	{}

	void doUndo() override {
		oRepo.addOffer(oldOffer);
	}
};

class undoMod : public undoAction {
private:
	offer oldOffer, newOffer;
	offersRepository& oRepo;

public:
	undoMod(const offer& oldOffer, const offer& newOffer, offersRepository& oRepo) :
		oldOffer{ oldOffer },
		newOffer{ newOffer },
		oRepo{ oRepo }
	{}

	void doUndo() override {
		oRepo.popOffer(newOffer.getId());
		oRepo.addOffer(oldOffer);
	}
};