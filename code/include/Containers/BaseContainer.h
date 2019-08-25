#ifndef DE_BASECONTAINER_H
#define DE_BASECONTAINER_H

#include "Basic.h"
#include "Allocator.h"

namespace DE {

/*!
  \brief Generic container.
*/
class BaseContainer : public DE_Class {

protected:

  u32 mLength;
  u32 mElementSize;
  u32 mAlignment;
  Allocator* mAllocator;

  void init(u32 length, u32 elementSize, u32 alignment);

public:

  DE_CLASS(BaseContainer, DE_Class)

  /*!
    \return Container length.
  */
  u32 getLength() const;

  /*!
    \return Container element size.
  */
  u32 getElementSize() const;

  /*!
    \return Container alignment.
  */
  u32 getAlignment() const;

  /*!
    \brief Sets the allocator.
    \param allocator Pointer to Allocator.
  */
  void setAllocator(Allocator* allocator);

  /*!
    \brief Clear the container.
  */
  virtual void clear();
};

} /* namespace DE */

#endif /* DE_BASECONTAINER_H */
