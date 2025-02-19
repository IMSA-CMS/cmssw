// -*- C++ -*-
#ifndef Fireworks_Core_FWNavigatorBase_h
#define Fireworks_Core_FWNavigatorBase_h
//
// Package:     newVersion
// Class  :     CmsShowNavigator
//

// system include files
#include <string>
#include <sigc++/sigc++.h>
#include <Rtypes.h>

// user include files
#include "Fireworks/Core/interface/FWConfigurable.h"

#include "DataFormats/Provenance/interface/EventID.h"

// forward declarations
class CmsShowMainBase;

namespace edm {
  class EventBase;
  class EventID;
}  // namespace edm

class FWNavigatorBase : public FWConfigurable {
public:
  enum EFilterState { kOff, kOn, kWithdrawn };
  enum EFilterMode { kOr = 1, kAnd = 2 };

public:
  FWNavigatorBase(const CmsShowMainBase&);
  ~FWNavigatorBase() override;

  //configuration management interface
  void addTo(FWConfiguration&) const override = 0;
  void setFrom(const FWConfiguration&) override = 0;

  virtual void nextEvent() = 0;
  virtual void previousEvent() = 0;
  virtual bool nextSelectedEvent() = 0;
  virtual bool previousSelectedEvent() = 0;
  virtual void firstEvent() = 0;
  virtual void lastEvent() = 0;
  // FIXME -- should be Long64_t.
  virtual void goToRunEvent(edm::RunNumber_t, edm::LuminosityBlockNumber_t, edm::EventNumber_t) = 0;

  virtual bool isLastEvent() = 0;
  virtual bool isFirstEvent() = 0;

  virtual const edm::EventBase* getCurrentEvent() const = 0;
  virtual int getNSelectedEvents() = 0;
  virtual int getNTotalEvents() = 0;

  sigc::signal<void> newEvent_;

  FWNavigatorBase(const FWNavigatorBase&) = delete;                   // stop default
  const FWNavigatorBase& operator=(const FWNavigatorBase&) = delete;  // stop default

private:
  // ---------- member data --------------------------------
  // entry is an event index nubmer which runs from 0 to
  // #events or #selected_events depending on if we filter
  // events or not
  const CmsShowMainBase& m_main;
};

#endif
