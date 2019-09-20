defmodule Sort do

  # Sort a list with selection sort

  # Empty list? Done.
  def ssort([]) do
    []
  end

  # Non-empty list
  def ssort(xs) do
    # Get smallest element using library function
    first = Enum.min(xs)
    # Remove that from rest of list
    rest  = drop_one(xs, first)
    # Result: First item followed by sort(rest)
    [ first | ssort(rest) ]
  end

  # Remove one instance of 'item' from list.
  def drop_one(xs, item) do
    if xs == [] do
      []
    else
      # hd gets first item
      # tl drops first item
      if hd(xs) == item do
        tl(xs)
      else
        [ hd(xs) | drop_one(tl(xs), item) ]
      end
    end
  end

  # Alternate drop_one
  def drop_one_([], _), do: []
  def drop_one_([x|xs], item) do
    if x == item do
      xs
    else
      [ x | drop_one_(xs, item) ]
    end
  end

  # Sort a list with insertion sort
  def isort(xs) do
    isort(xs, [])   # Insert each item into initally empty sorted list.
  end

  # If input list is empty, return output
  def isort([], ys) do
    ys
  end

  # Else insert first item into sorted list
  def isort([x|xs], ys) do
    isort(xs, insert_sorted(x, ys))
  end

  def insert_sorted(x, []), do: [x]
  def insert_sorted(x, [head|tail] = ys) do
    if x < head do
      [x | ys]
    else
      [head | insert_sorted(x, tail)]
    end
  end

  # Alternate insertion sort
  def isort2(xs) do
    Enum.reduce xs, [], &insert_sorted/2
  end
end


IO.inspect Sort.ssort([1,3,5,7,2,4,6,8])
IO.inspect Sort.isort([1,3,5,7,2,4,6,8])
IO.inspect Sort.isort2([1,3,5,7,2,4,6,8])
