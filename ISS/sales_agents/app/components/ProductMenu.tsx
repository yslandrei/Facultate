'use client'
import { Product } from '@/types/Product';
import { ProductFilters, SortType } from '@/types/ProductFilters';
import React, { useEffect, useState } from 'react';
import RangeSlider from './RangeSlider';
import { BASE_URL } from '@/types/constants';
import Pagination from '@mui/material/Pagination';
import FiltersTab from './FiltersTab';
import ProductTable from './ProductTable';
import { User } from '@/types/User';
import SockJsClient from 'react-stomp';

interface ProductMenuProps {
  user: User
}

const ProductMenu: React.FC<ProductMenuProps> = ({ user }) => {
  const [products, setProducts] = useState<Product[]>([])
  const [totalPages, setTotalPages] = useState<number>()

  const [defaultPriceRange, setDefaultPriceRange] = useState<{ min: number, max: number }>()
  const [defaultQuantityRange, setDefaultQuantityRange] = useState<{ min: number, max: number }>()

  const [filters, setFilters] = useState<ProductFilters>({
    page: 1,
    sortType: SortType.NONE,
    name: '',
    minPrice: undefined,
    maxPrice: undefined,
    minQuantity: undefined,
    maxQuantity: undefined
  })

  const handleRefreshProducts = () => {
    fetch(`${BASE_URL}/product/filter`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Access-Control-Allow-Origin': '*'
      },
      body: JSON.stringify(filters)
    })
      .then(response => response.json())
      .then(data => {
        setProducts(data.content)
        setTotalPages(data.totalPages ? data.totalPages : 1)
      }).then(() => {
        fetch(`${BASE_URL}/product/ranges`)
          .then(response => response.json())
          .then(data => {
            setDefaultPriceRange({ min: data.minPrice, max: data.maxPrice })
            setDefaultQuantityRange({ min: data.minQuantity, max: data.maxQuantity })
          })
      })
  }

  useEffect(() => {
    if (filters.minPrice !== undefined) {
      fetch(`${BASE_URL}/product/filter`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'Access-Control-Allow-Origin': '*'
        },
        body: JSON.stringify(filters)
      })
        .then(response => response.json())
        .then(data => {
          setProducts(data.content)
          setTotalPages(data.totalPages ? data.totalPages : 1)
        })
    }
  }, [filters])


  return <>
    <SockJsClient
      url={"http://localhost:8080/ws"}
      topics={['/topic/updates']}
      onConnect={() => console.log("Connected!")}
      onDisconnect={console.log("Disconnected!")}
      onMessage={(msg: any) => handleRefreshProducts()}
      debug={false}
    />
    <div className=" flex flex-col space-y-4 ">

      <FiltersTab
        filters={filters}
        setFilters={setFilters}
        defaultPriceRange={defaultPriceRange}
        setDefaultPriceRange={setDefaultPriceRange}
        defaultQuantityRange={defaultQuantityRange}
        setDefaultQuantityRange={setDefaultQuantityRange}
      />

      <ProductTable
        products={products}
        user={user}
        filters={filters}
        setFilters={setFilters}
      />

      {totalPages &&
        <div className='flex justify-center'>
          <Pagination
            color='primary'
            sx={{
              '.MuiPaginationItem-root': {
                color: 'white',
                fontWeight: 'bold',
                fontSize: '1rem',
                fontFamily: 'inherit'
              },
            }}
            count={totalPages}
            page={filters.page}
            onChange={(e, value: number) => setFilters({ ...filters, page: value })}
          />
        </div>
      }
    </div>
  </>
}

export default ProductMenu;