cmake_minimum_required(VERSION 3.22)

project(noisegen VERSION 1.0.0)

# ==============================================================================
# 1. On charge JUCE depuis le chemin relatif défini dans ton ancien projet
# ==============================================================================
add_subdirectory(../juce-8.0.8-windows/JUCE juce_build)

# ==============================================================================
# 2. On déclare ton projet comme étant une application console
# ==============================================================================
juce_add_console_app(noisegen PRODUCT_NAME "noisegen")

# ==============================================================================
# 3. On ajoute tous les fichiers sources de ton projet (tirés de ton .jucer)
# ==============================================================================
target_sources(noisegen PRIVATE
    Source/Core/PinkNoise.cpp
    Source/Core/PinkNoise.h
    Source/Core/SimplePinkNoise.cpp
    Source/Core/SimplePinkNoise.h
    Source/Core/BrownNoise.cpp
    Source/Core/BrownNoise.h
    Source/Core/NoiseGenerator.h
    Source/Core/NoiseRunner.cpp
    Source/Core/NoiseRunner.h
    Source/Core/WhiteNoise.cpp
    Source/Core/WhiteNoise.h
    Source/Runs/RunWhiteNoise.cpp
)

# On définit le standard C++ (C++17 ou C++20)
target_compile_features(noisegen PRIVATE cxx_std_17)

# On ajoute l'option JUCE qui était activée dans ton .jucer
target_compile_definitions(noisegen PRIVATE
    JUCE_STRICT_REFCOUNTEDPOINTER=1
)

# ==============================================================================
# 4. On lie tous les modules JUCE qui étaient cochés dans Projucer
# ==============================================================================
target_link_libraries(noisegen PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
)

# ==============================================================================
# 5. On demande à JUCE de générer le fichier "JuceHeader.h" en tâche de fond
# Cela permet à tes anciens fichiers de compiler sans rien modifier !
# ==============================================================================
juce_generate_juce_header(noisegen)
