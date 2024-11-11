# SPDX-License-Identifier: GPL-3.0-only
# SPDX-FileCopyrightText: 2024 Trần Nam Tuấn <tuantran1632001@gmail.com>

add_executable(qvanced)

ecm_add_qml_module(qvanced
    URI io.github.thebill2001.qvanced
    VERSION 1.0
)

target_sources(qvanced
    PRIVATE
        main.cpp
        app.cpp
)

ecm_target_qml_sources(qvanced
    SOURCES
            contents/ui/Main.qml
            contents/ui/About.qml
)

kconfig_add_kcfg_files(qvanced GENERATE_MOC qvancedconfig.kcfgc)

target_link_libraries(qvanced
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    Qt6::QuickControls2
    Qt6::Widgets
    KF6::I18n
    KF6::CoreAddons
    KF6::ConfigCore
    KF6::ConfigQml
    KF6::IconThemes
)

install(TARGETS qvanced ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
