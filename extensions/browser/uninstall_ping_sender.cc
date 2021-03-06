// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "extensions/browser/uninstall_ping_sender.h"

#include "base/version.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/updater/update_service.h"

namespace extensions {

UninstallPingSender::UninstallPingSender(ExtensionRegistry* registry,
                                         const Filter& filter)
    : filter_(filter), observer_(this) {
  observer_.Add(registry);
}

UninstallPingSender::~UninstallPingSender() {}

void UninstallPingSender::OnExtensionUninstalled(
    content::BrowserContext* browser_context,
    const Extension* extension,
    UninstallReason reason) {
  LOG(INFO) << "[EXTENSIONS] UninstallPingSender::OnExtensionUninstall - Step 1";
  if (filter_.Run(extension, reason) == SEND_PING) {
    LOG(INFO) << "[EXTENSIONS] UninstallPingSender::OnExtensionUninstall - Step 2";
    UpdateService* updater = UpdateService::Get(browser_context);
    LOG(INFO) << "[EXTENSIONS] UninstallPingSender::OnExtensionUninstall - Step 3";
    updater->SendUninstallPing(extension->id(), extension->version(), reason);
    LOG(INFO) << "[EXTENSIONS] UninstallPingSender::OnExtensionUninstall - Step 4";
  }
  LOG(INFO) << "[EXTENSIONS] UninstallPingSender::OnExtensionUninstall - Step 5";
}

}  // namespace extensions
