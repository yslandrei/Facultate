import { Slider } from "@mui/material";

interface RangeSliderProps {
  label: string;
  min: number;
  max: number;
  value: number[];
  onChange: (e: Event, newValue: number | number[]) => void;
}
//TODO: use a better slider that updates dinamically when min and max are changed
const RangeSlider: React.FC<RangeSliderProps> = ({label, min, max, value, onChange}) => {
  return (
    <div className="flex flex-col items-center w-72 bg-blue-500 px-6 py-2 rounded-md">
      <label><b>{label}:</b> {value[0]} - {value[1]}</label>
      <Slider
        min={min}
        max={max}
        value={value}
        // @ts-ignore
        color="white"
        // @ts-ignore
        onChange={onChange}
        valueLabelDisplay="off"
      />
    </div>
  )
}

export default RangeSlider;