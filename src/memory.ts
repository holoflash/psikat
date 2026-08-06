// I'm not feeling using objects for the application state.
// Here's me trying to think more "low-level" and see if I can figure out using an ArrayBuffer instead.

const STATE_SIZE = 16; // Lets start small

// An ArrayBuffer can be passed to a worker using .postMessage()
// Will for sure come in handy later if I store pattern data like this.
const data_buffer = new ArrayBuffer(STATE_SIZE);

const BPM = 0; // 16bit
const TRACK_COUNT = 2; // 8bit

// This one's for settings/getting 8bits at a time
const data_bytes = new Uint8Array(data_buffer);
data_bytes[TRACK_COUNT] = 12;
// BUT can also be used to zero out a range
data_bytes.fill(0, 0, 10);
// OR to set multiple bytes at once by passing an array
data_bytes.set([1, 2, 3, 4, 5, 6], 2); // THIS will be very useful
// Have to read more here to find more useful methods
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/TypedArray

// DataView can be used to set/get larger values that cover more than 8bits
const data_view = new DataView(data_buffer);
data_view.setInt16(BPM, 32767);
console.log(data_view.getInt16(BPM));
// Other than that, I'm not fully convinced yet that It will be very useful here

console.log(data_bytes[BPM]);
console.log(data_bytes[TRACK_COUNT]);

// This will be great for Cloning patterns for example!
data_bytes.copyWithin(5, 0, 4);

// Ok I just realized that prettu much all array methods I'm just to work on an Uint8Array too!
