const sequence = [0, 1023, 1023, 1023, 512, 512, 256, 256];
const expected = [0, 127, 239, 337, 358, 377, 361, 347];
const FILTER_SHIFT = 3;

let initialized = false;
let value = 0;
const actual = [];

for (const sample of sequence) {
  if (!initialized) {
    value = sample;
    initialized = true;
  } else {
    const delta = sample - value;
    value = value + (delta >> FILTER_SHIFT);
  }

  actual.push(value);
}

let failures = 0;
for (let i = 0; i < expected.length; i++) {
  if (actual[i] !== expected[i]) {
    console.error(`FAIL filtro indice ${i}: esperado ${expected[i]}, obtido ${actual[i]}`);
    failures++;
  }
}

if (failures > 0) {
  process.exit(1);
}

console.log("PASS filtro passa-baixas");
