/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

Cu.import("resource://gre/modules/Services.jsm");

var StartUI = {
  get startUI() { return document.getElementById("start-container"); },

  get maxResultsPerSection() {
    return Services.prefs.getIntPref("browser.display.startUI.maxresults");
  },

  get chromeWin() {
    // XXX Not e10s friendly. We use this in a few places.
    return Services.wm.getMostRecentWindow('navigator:browser');
  },

  init: function init() {
    this.startUI.addEventListener("click", this, false);
    this.startUI.addEventListener("MozMousePixelScroll", this, false);

    // Update the input type on our local broadcaster
    document.getElementById("bcast_preciseInput").setAttribute("input",
      this.chromeWin.InputSourceHelper.isPrecise ? "precise" : "imprecise");

    this._adjustDOMforViewState();

    TopSitesStartView.init();
    BookmarksStartView.init();
    HistoryStartView.init();
    RemoteTabsStartView.init();

    this.chromeWin.addEventListener("MozPrecisePointer", this, true);
    this.chromeWin.addEventListener("MozImprecisePointer", this, true);
    Services.obs.addObserver(this, "metro_viewstate_changed", false);
  },

  uninit: function() {
    if (TopSitesStartView)
      TopSitesStartView.uninit();
    if (BookmarksStartView)
      BookmarksStartView.uninit();
    if (HistoryStartView)
      HistoryStartView.uninit();
    if (RemoteTabsStartView)
      RemoteTabsStartView.uninit();

    if (this.chromeWin) {
      this.chromeWin.removeEventListener("MozPrecisePointer", this, true);
      this.chromeWin.removeEventListener("MozImprecisePointer", this, true);
    }
    Services.obs.removeObserver(this, "metro_viewstate_changed");
  },

  goToURI: function (aURI) {
    this.chromeWin.BrowserUI.goToURI(aURI);
  },

  onClick: function onClick(aEvent) {
    // If someone clicks / taps in empty grid space, take away
    // focus from the nav bar edit so the soft keyboard will hide.
    this.chromeWin.BrowserUI.blurNavBar();

    if (aEvent.button == 0) {
      this.chromeWin.ContextUI.dismissTabs();
    }
  },

  onNarrowTitleClick: function onNarrowTitleClick(sectionId) {
    let section = document.getElementById(sectionId);

    if (section.hasAttribute("expanded"))
      return;

    for (let expandedSection of this.startUI.querySelectorAll(".meta-section[expanded]"))
      expandedSection.removeAttribute("expanded")

    section.setAttribute("expanded", "true");
  },

  handleEvent: function handleEvent(aEvent) {
    switch (aEvent.type) {
      case "MozPrecisePointer":
        document.getElementById("bcast_preciseInput").setAttribute("input", "precise");
        break;
      case "MozImprecisePointer":
        document.getElementById("bcast_preciseInput").setAttribute("input", "imprecise");
        break;
      case "click":
        this.onClick(aEvent);
        break;
      case "MozMousePixelScroll":
        let viewstate = this.startUI.getAttribute("viewstate");
        if (viewstate === "snapped" || viewstate === "portrait") {
          window.scrollBy(0, aEvent.detail);
        } else {
          window.scrollBy(aEvent.detail, 0);
        }

        aEvent.preventDefault();
        aEvent.stopPropagation();
        break;
    }
  },

  _adjustDOMforViewState: function(aState) {
    let currViewState = aState;
    if (!currViewState && Services.metro.immersive) {
      switch (Services.metro.snappedState) {
        case Ci.nsIWinMetroUtils.fullScreenLandscape:
          currViewState = "landscape";
          break;
        case Ci.nsIWinMetroUtils.fullScreenPortrait:
          currViewState = "portrait";
          break;
        case Ci.nsIWinMetroUtils.filled:
          currViewState = "filled";
          break;
        case Ci.nsIWinMetroUtils.snapped:
          currViewState = "snapped";
          break;
      }
    }

    document.getElementById("bcast_windowState").setAttribute("viewstate", currViewState);
    if (currViewState == "snapped") {
      document.getElementById("start-topsites-grid").removeAttribute("tiletype");
    } else {
      document.getElementById("start-topsites-grid").setAttribute("tiletype", "thumbnail");
    }
  },

  observe: function (aSubject, aTopic, aData) {
    switch (aTopic) {
      case "metro_viewstate_changed":
        this._adjustDOMforViewState(aData);
        break;
    }
  }
};
