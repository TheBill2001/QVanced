# SPDX-FileCopyrightText: 2024 Trần Nam Tuấn <tuantran1632001@gmail.com>
# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.21)

project(qvanced VERSION 0.0.1)

set(QT6_MIN_VERSION 6.5.0)
set(KF6_MIN_VERSION 6.0.0)

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)

if(${CMAKE_VERSION} VERSION_GREATER 3.30)
    cmake_policy(SET CMP0175 OLD)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(ECMFindQmlModule)
include(KDEGitCommitHooks)
include(KDEClangFormat)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX QVANCED
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/version-qvanced.h"
)

find_package(Qt6 ${QT6_MIN_VERSION} REQUIRED COMPONENTS Core Gui Qml QuickControls2 Widgets)
find_package(KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS Kirigami I18n CoreAddons Config QQC2DesktopStyle IconThemes)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

ecm_find_qmlmodule(org.kde.desktop ${KF6_MIN_VERSION})
ecm_find_qmlmodule(org.kde.kirigami ${KF6_MIN_VERSION} REQUIRED)
ecm_find_qmlmodule(org.kde.kirigamiaddons.formcard 1.3 REQUIRED)

add_subdirectory(src)

configure_file(io.github.thebill2001.qvanced.desktop.in io.github.thebill2001.qvanced.desktop @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/io.github.thebill2001.qvanced.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES io.github.thebill2001.qvanced.metainfo.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
ki18n_install(po)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
