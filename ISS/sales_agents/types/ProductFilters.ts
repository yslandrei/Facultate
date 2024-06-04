export interface ProductFilters {
  page: number;
  sortType: SortType;
  name: string;
  minPrice: undefined | number;
  maxPrice: undefined | number;
  minQuantity: undefined | number;
  maxQuantity: undefined | number;
}

export enum SortType {
  NONE, 
  ASC_NAME, 
  DESC_NAME, 
  ASC_PRICE, 
  DESC_PRICE, 
  ASC_QUANTITY, 
  DESC_QUANTITY
}
