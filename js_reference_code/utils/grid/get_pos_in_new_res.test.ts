import { describe, expect, test } from "vite-plus/test";
import { get_pos_in_new_res } from "./get_pos_in_new_res";

describe("get_pos_in_new_res", () => {
  describe("Same resolution", () => {
    test("Returns the position unchanged", () => {
      expect(get_pos_in_new_res(16, 16, 7)).toBe(7);
    });
    test("Returns zero unchanged", () => {
      expect(get_pos_in_new_res(32, 32, 0)).toBe(0);
    });
  });

  describe("Even-to-odd", () => {
    describe("Low-to-high", () => {
      test("Far apart", () => {
        expect(get_pos_in_new_res(8, 48, 5)).toBe(30);
      });
      test("Nearby", () => {
        expect(get_pos_in_new_res(8, 24, 5)).toBe(15);
      });
      test("Neighbors", () => {
        expect(get_pos_in_new_res(4, 6, 3)).toBe(4);
      });
      test("Neighbors, higher position", () => {
        expect(get_pos_in_new_res(6, 8, 5)).toBe(6);
      });
    });
    describe("High-to-low", () => {
      test("Far apart", () => {
        expect(get_pos_in_new_res(48, 8, 7)).toBe(1);
      });
      test("Nearby", () => {
        expect(get_pos_in_new_res(24, 8, 15)).toBe(5);
      });
    });
  });

  describe("Even-to-even", () => {
    describe("Low-to-high", () => {
      test("Far apart", () => {
        expect(get_pos_in_new_res(4, 128, 3)).toBe(96);
      });
      test("Nearby", () => {
        expect(get_pos_in_new_res(8, 32, 5)).toBe(20);
      });
      test("Neighbors", () => {
        expect(get_pos_in_new_res(64, 128, 0)).toBe(0);
      });
    });
    describe("High-to-low", () => {
      test("Far apart", () => {
        expect(get_pos_in_new_res(128, 4, 96)).toBe(3);
      });
    });
  });

  describe("Odd-to-even", () => {
    describe("Low-to-high", () => {
      test("Far apart", () => {
        expect(get_pos_in_new_res(12, 128, 6)).toBe(64);
      });
      test("Nearby", () => {
        expect(get_pos_in_new_res(24, 64, 12)).toBe(32);
      });
      test("Neighbors", () => {
        expect(get_pos_in_new_res(12, 16, 9)).toBe(12);
      });
    });
  });

  describe("Odd-to-odd", () => {
    describe("Low-to-high", () => {
      test("Far apart", () => {
        expect(get_pos_in_new_res(6, 96, 5)).toBe(80);
      });
      test("Nearby", () => {
        expect(get_pos_in_new_res(12, 48, 7)).toBe(28);
      });
      test("Neighbors", () => {
        expect(get_pos_in_new_res(6, 12, 3)).toBe(6);
      });
    });
  });
});
