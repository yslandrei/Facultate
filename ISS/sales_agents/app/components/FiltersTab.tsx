'use client'
import { ProductFilters } from "@/types/ProductFilters";
import RangeSlider from "./RangeSlider";
import { useEffect, useState } from "react";
import { BASE_URL } from "@/types/constants";

interface FiltersTabProps {
  filters: ProductFilters;
  setFilters: React.Dispatch<React.SetStateAction<ProductFilters>>;
  defaultPriceRange: { min: number, max: number } | undefined;
  setDefaultPriceRange: React.Dispatch<React.SetStateAction<{ min: number; max: number } | undefined>>;
  defaultQuantityRange: { min: number, max: number } | undefined;
  setDefaultQuantityRange: React.Dispatch<React.SetStateAction<{ min: number; max: number } | undefined>>;
}

const FiltersTab: React.FC<FiltersTabProps> = ({ filters, setFilters, defaultPriceRange, setDefaultPriceRange, defaultQuantityRange, setDefaultQuantityRange }) => {
  
  useEffect(() => {
    fetch(`${BASE_URL}/product/ranges`)
      .then(response => response.json())
      .then(data => {
        setDefaultPriceRange({ min: data.minPrice, max: data.maxPrice })
        setDefaultQuantityRange({ min: data.minQuantity, max: data.maxQuantity })
        setFilters({
          ...filters,
          minPrice: data.minPrice,
          maxPrice: data.maxPrice,
          minQuantity: data.minQuantity,
          maxQuantity: data.maxQuantity
        })
      })
  }, [])
  
  return <>
    {filters.minPrice && filters.maxPrice && filters.minQuantity && filters.maxQuantity && defaultPriceRange && defaultQuantityRange &&
      <div className='flex space-x-4'>
        <input
          type="text"
          placeholder="Search by name"
          className="border px-6 w-72 rounded-md outline-none text-black"
          value={filters.name}
          onChange={(e) => setFilters({ ...filters, page: 1 , name: e.target.value })}
        />
        <RangeSlider
          label="Quantity Range"
          min={defaultQuantityRange.min}
          max={defaultQuantityRange.max}
          value={[filters.minQuantity, filters.maxQuantity]}
          // @ts-ignore
          onChange={(e: Event, newValue: number | number[]) => setFilters({ ...filters, page: 1 , minQuantity: newValue[0], maxQuantity: newValue[1] })}
        />
        <RangeSlider
          label="Price Range"
          min={defaultPriceRange.min}
          max={defaultPriceRange.max}
          value={[filters.minPrice, filters.maxPrice]}
          // @ts-ignore
          onChange={(e: Event, newValue: number | number[]) => setFilters({ ...filters, page: 1 , minPrice: newValue[0], maxPrice: newValue[1] })}
        />
      </div>
    }
  </>
}

export default FiltersTab;