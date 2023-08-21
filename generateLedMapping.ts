// bespoke worm spec
const ledRuns = [
  [6, 4, 5, 6],
  [6, 4, 5, 7],
  [6, 5, 4, 7],
  [5, 5, 5, 8],
  [6, 5, 4, 0],
  [5, 8, 4, 0],
  [5, 9, 5, 0],
  [5, 9, 5, 0],
  [6, 9, 5, 0],
  [5, 8, 5, 0],
  [4, 9, 5, 0],
  [5, 9, 5, 0],
  [5, 9, 4, 0],
  [5, 7, 4, 0],
  [5, 7, 4, 0],
  [5, 5, 5, 7],
  [5, 5, 5, 6],
  [6, 4, 5, 7],
];
const annularLedsPerRun = [
  1, 1, 1, 2, 1, 2, 0, 1, 1, 1, 0, 1, 1, 2, 1, 1, 0, 0,
];

const calculatePosition = (
  segmentIndex,
  segmentLedIndex,
  segmentLedCount,
  isForwardRun,
) => {
  let position = segmentIndex * 0.25;
  position += (segmentLedIndex / segmentLedCount) * 0.25;
  if (!isForwardRun) {
    // position=
  }
};

// this is the final mapping from LED index to linear position along the worm
const ledIndexToPosition: number[] = [];

let ledIndex = 0;
ledRuns.forEach((ledRun, runIndex) => {
  // every other run is forwards/backwards in terms of data direction
  const isForwardRun = runIndex % 2 === 0;

  if (isForwardRun) {
    // iterate through the segments of this run FORWARDS
    ledRun.forEach((segmentLedCount, segmentIndex) => {
      // iterate through the LEDs of this segment FORWARDS
      for (let i = 0; i < segmentLedCount; i++) {
        ledIndexToPosition.push(); // TODO:
        ledIndex++;
      }
    });
  } else {
    // iterate through the segments of this run BACKWARDS
    for (
      let segmentIndex = ledRun.length - 1;
      segmentIndex >= 0;
      segmentIndex--
    ) {
      // iterate through the LEDs of this segment BACKWARDS
      for (let i = ledRun[segmentIndex] - 1; i >= 0; i--) {
        ledIndexToPosition.push(); // TODO:
        ledIndex++;
      }
    }
  }

  for (let i = 0; i < annularLedsPerRun[runIndex]; i++) {
    // for annular LEDs, we just repeat the last LED
    ledIndexToPosition.push(ledIndexToPosition[ledIndexToPosition.length - 1]);
    ledIndex++;
  }
});

const output = {};
