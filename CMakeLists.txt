cmake_minimum_required(VERSION 3.20)

project(QVanced VERSION 0.0.1 LANGUAGES CXX)

set(QT6_MIN_VERSION 6.5.0)
set(KF6_MIN_VERSION 6.0.0)

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(ECMFindQmlModule)
include(ECMQmlModule)

include(KDEGitCommitHooks)
include(KDEClangFormat)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX QVANCED
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/version-qvanced.h"
)

find_package(Qt6 ${QT6_MIN_VERSION} REQUIRED COMPONENTS
    Core
    Quick
    Gui
    QuickControls2
    Svg
    Widgets
)

find_package(KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS
    Kirigami
    I18n
    CoreAddons
    QQC2DesktopStyle
    IconThemes
    Config
)

find_package(LibXml2 REQUIRED)

# qt_policy(SET QTP0001 NEW)

ecm_find_qmlmodule(org.kde.kirigamiaddons.formcard REQUIRED)
ecm_find_qmlmodule(org.kde.kirigami REQUIRED)

add_subdirectory(src)

# install(PROGRAMS io.github.thebill2001.qvanced.desktop DESTINATION ${KDE_INSTALL_APPDIR})

include(FeatureSummary)
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
