import SwiftUI
import AudioUnit

final class AudioUnitState: ObservableObject {
    private let player: OpaquePointer = launch()
    @Published var is_playing: Bool = false

    deinit {
        audio_unit_destroy(player)
    }

    func toggle_playback() {
        if is_playing {
            audio_unit_stop(player)
            is_playing = false
        } else {
            audio_unit_start(player)
            is_playing = true
        }
    }
}

struct ContentView: View {
    @StateObject private var audio_unit = AudioUnitState()

    var body: some View {
        VStack() {
            Text("psikat")
            Button(action: {
                audio_unit.toggle_playback()
            }) {
                Label(audio_unit.is_playing ? "Stop" : "Play", 
                      systemImage: audio_unit.is_playing ? "stop.fill" : "play.fill")
            }
        }
    }
}

@main
struct Psikat: App {
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}