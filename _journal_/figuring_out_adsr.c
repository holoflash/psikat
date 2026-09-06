
int main(void) {
    /* ADSR
    1. create a new GAIN variable
    2. Based on ADSR settings, multiply the sample by this gain, but in time.
     */

    double duration_in_samples = 400.0;
    double attack              = 0.2; // let's say the attack should be 20% of the whole note duration
    double gain_right_now      = 0.0;
    double max_gain            = 1.0;
    // in 20% of the note duration - go from 0 to desired gain level
    while (duration_in_samples < duration_in_samples * attack) {
        // Increase the gain incrementally for the length of the attack phase
        // Until we reach app->transport.master_volume
        // need to find out how much to change the gain for each sample
        // to reach the desired gain in time

        // if duration in samples is 400.0 and our max gain is 1.0
    }
}
