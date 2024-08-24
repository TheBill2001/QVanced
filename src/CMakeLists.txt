add_executable(qvanced)

ecm_add_qml_module(qvanced
    URI io.github.thebill2001.qvanced
    VERSION 1.0
)

ecm_target_qml_sources(qvanced
    SOURCES
        contents/ui/Main.qml
        contents/ui/About.qml
)

target_sources(qvanced PUBLIC
    main.cpp

    qvancedglobal.h
    utils/network.h
    # utils/htmlparser.h utils/htmlparser.cpp

    qvancedapp.h qvancedapp.cpp
    apkprovider/apkproviderabstract.h apkprovider/apkproviderabstract.cpp
    apkprovider/apkmirrorprovider.h apkprovider/apkmirrorprovider.cpp
)

target_include_directories(qvanced
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/apkprovider
)

target_link_libraries(qvanced
    PRIVATE
        # Qt Framework
        Qt6::Quick
        Qt6::Qml
        Qt6::Gui
        Qt6::QuickControls2
        Qt6::Widgets

        # KDE Framework
        KF6::I18n
        KF6::CoreAddons
        KF6::IconThemes
        KF6::ConfigCore
        KF6::ConfigGui

        # HTML parser
        LibXml2::LibXml2
)

install(TARGETS qvanced ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
