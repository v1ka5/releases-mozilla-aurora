/* -*- Mode: C++; c-basic-offset: 2; indent-tabs-mode: nil; tab-width: 8 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla IPDL Test Harness.
 *
 * The Initial Developer of the Original Code is
 *   Chris Jones <jones.chris.g@gmail.com>.
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef ipc_test_harness_TestParent_h
#define ipc_test_harness_TestParent_h 1

#include "mozilla/test/PTestParent.h"

namespace mozilla {
namespace test {

// Header file contents
class TestParent : public PTestParent
{
protected:
#if 1
//-----------------------------------------------------------------------------
// "Hello world" example
    virtual nsresult RecvWorld();


#elif 0
//-----------------------------------------------------------------------------
// Example solution to exercise
    virtual nsresult RecvPing();
    virtual nsresult RecvPong(const int& status);
    virtual nsresult RecvGetValue(const String& key);
    virtual nsresult RecvGetValues(const StringArray& keys);
    virtual nsresult RecvSetValue(
                const String& key,
                const String& val,
                bool* ok);
#endif

public:
    TestParent();
    virtual ~TestParent();

    void DoStuff();
};

} // namespace test
} // namespace mozilla

#endif /* ipc_test_harness_TestParent_h */
