import * as fs from "fs";

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
  [5, 7, 4, 7],
  [5, 5, 5, 7],
  [5, 5, 5, 6],
  [6, 4, 5, 7],
];
const annularLedsPerRun = [
  1, 1, 1, 2, 1, 2, 0, 1, 1, 1, 0, 1, 1, 2, 1, 1, 0, 0,
];

// 6+6+6+5+6+5+5+5+6+5+4+5+5+5+5+5+5+6
// =95

// 4+4+5+5+5+8+9+9+9+8+9+9+9+7+7+5+5+4
// =121

// 5+5+4+5+4+4+5+5+5+5+5+5+4+4+4+5+5+5
// =84

// 6+7+7+8+0+0+0+0+0+0+0+0+0+0+7+7+6+7
// =55

// // test case
// const ledRuns = [
//   [2, 2],
//   [2, 2],
//   [2, 2],
// ];
// const annularLedsPerRun = [1, 1, 0];

const saveJson = (filename: string, data: any) =>
  fs.writeFileSync(filename, JSON.stringify(data));

const calculatePosition = (
  segmentIndex: number,
  segmentLedIndex: number,
  segmentLedCount: number,
) => {
  let position = segmentIndex * 0.25;
  position += (segmentLedIndex / segmentLedCount) * 0.25;
  return position;
};

// this is the final mapping from LED index to linear position along the worm
const ledIndexToPosition: number[] = [];

ledRuns.forEach((ledRun, runIndex) => {
  // every other run is forwards/backwards in terms of data direction
  const isForwardRun = runIndex % 2 === 0;

  if (isForwardRun) {
    // iterate through the segments of this run FORWARDS
    ledRun.forEach((segmentLedCount, segmentIndex) => {
      // iterate through the LEDs of this segment FORWARDS
      for (let i = 0; i < segmentLedCount; i++) {
        ledIndexToPosition.push(
          calculatePosition(segmentIndex, i, segmentLedCount),
        );
      }
    });
  } else {
    // iterate through the segments of this run BACKWARDS
    for (
      let segmentIndex = ledRun.length - 1;
      segmentIndex >= 0;
      segmentIndex--
    ) {
      const segmentLedCount = ledRun[segmentIndex];
      // iterate through the LEDs of this segment BACKWARDS
      for (let i = ledRun[segmentIndex] - 1; i >= 0; i--) {
        ledIndexToPosition.push(
          calculatePosition(segmentIndex, i, segmentLedCount),
        );
      }
    }
  }

  for (let i = 0; i < annularLedsPerRun[runIndex]; i++) {
    // for annular LEDs, we just repeat the last LED
    ledIndexToPosition.push(ledIndexToPosition[ledIndexToPosition.length - 1]);
  }
});

const outputFileName = "ledMapping.json";
saveJson(outputFileName, ledIndexToPosition);
console.log(ledIndexToPosition.length);
